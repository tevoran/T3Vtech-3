#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

extern GLuint tt_gfx_3d_default_tex; //default texture

//helper functions
float tt_helper_aabb_select_new_extreme_max(
	float x_max,
	float x_min, 
	float y_max,
	float y_min, 
	float z_max,
	float z_min)
{
	float out=x_max;
	if(out < x_min)
	{
		out = x_min;
	}
	if(out < y_max)
	{
		out = y_max;
	}
	if(out < y_min)
	{
		out = y_min;
	}
	if(out < z_max)
	{
		out = z_max;
	}
	if(out < z_min)
	{
		out = z_min;
	}
	return out;
}

float tt_helper_aabb_select_new_extreme_min(
	float x_max,
	float x_min, 
	float y_max,
	float y_min, 
	float z_max,
	float z_min)
{
	float out=x_max;
	if(out > x_min)
	{
		out = x_min;
	}
	if(out > y_max)
	{
		out = y_max;
	}
	if(out > y_min)
	{
		out = y_min;
	}
	if(out > z_max)
	{
		out = z_max;
	}
	if(out > z_min)
	{
		out = z_min;
	}
	return out;
}


tt_3d_object* tt_3d_object_new() 
{
	//creating the 3d object and putting it into the render list
	tt_3d_object *new_object=malloc(sizeof(tt_3d_object));
	new_object->node=tt_list_new_node(tt_3d_list_entry_node);
	if(!tt_3d_list_entry_node) //save the entry node if it's one
	{
		tt_3d_list_entry_node=new_object->node;
	}
	tt_list_node_set_data(new_object->node, new_object);

	//initializing the object to default values
	new_object->num_indices=0;
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;

	tt_math_mat4_make_identity_matrix(&new_object->translation);
	tt_math_mat4_make_identity_matrix(&new_object->scale);
	tt_math_mat4_make_identity_matrix(&new_object->rotation);

	new_object->texture=tt_gfx_3d_default_tex;
	new_object->lighting_affected=true;
	new_object->size_bounding_sphere=0;
	new_object->invisibility_toggle=false; //make visible by default

	//setting the aabb to defaults
	new_object->aabb.x_max=0.0;
	new_object->aabb.x_min=0.0;
	new_object->aabb.y_max=0.0;
	new_object->aabb.y_min=0.0;
	new_object->aabb.z_max=0.0;
	new_object->aabb.z_min=0.0;

	return new_object;
}

//the function uses a pointer pointer so that the deleted object pointer can
//be set to NULL. This is done to reduce possible segfaults by accidentally
//deleting the same object twice.
void tt_3d_object_delete(tt_3d_object **object)
{
	//if this object has already been deleted then just quit
	if(*object==NULL)
	{
		return; 
	}

	//if this object is the first object in the render list
	if((*object)->node==tt_3d_list_entry_node)
	{
		tt_list_remove_node(&tt_3d_list_entry_node);
	}
	else
	{
		tt_list_remove_node(&(*object)->node);
	}

	free(*object);
	*object=NULL; //mark object as deleted
}

//transformations
void tt_3d_object_scale(tt_3d_object *object, tt_vec3 *scale)
{
	object->scale.array[0][0]=scale->x;
	object->scale.array[1][1]=scale->y;
	object->scale.array[2][2]=scale->z;
}

void tt_3d_object_set_position(tt_3d_object *object, tt_vec3 *position)
{
	object->translation.array[3][0]=position->x;
	object->translation.array[3][1]=position->y;
	object->translation.array[3][2]=position->z;
}

void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
{
	tt_mat4 rot_delta_mat=tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
	object->rotation=tt_math_mat4_mul(&rot_delta_mat, &object->rotation);
}

void tt_3d_object_rotate_like(tt_3d_object *object_target, tt_3d_object *object_already_rotated)
{
	object_target->rotation=object_already_rotated->rotation;
}


//setting object properties
void tt_3d_object_use_texture(tt_3d_object *object, tt_3d_texture *texture)
{
	if(texture) //use texture only if it exists
	{
		object->texture=texture->texture;
	}
	else //use default texture
	{
		object->texture=tt_gfx_3d_default_tex;
	}
}

void tt_3d_object_use_default_texture(tt_3d_object *object)
{
	object->texture=tt_gfx_3d_default_tex;
}

void tt_3d_object_light_affected(tt_3d_object *object, bool toggle)
{
	object->lighting_affected=toggle;
}

void tt_3d_object_make_invisible(tt_3d_object *object, bool toggle)
{
	object->invisibility_toggle=toggle;
}

//getting object properties
float tt_3d_object_get_bounding_sphere_size(tt_3d_object *object)
{
	return object->size_bounding_sphere;
}

//collisions
bool tt_3d_object_colliding_aabb(tt_3d_object *a, tt_3d_object *b)
{
	//transformations
	//scaling
	//object a
	tt_vec3 a_x_max_tmp;
		a_x_max_tmp.x=a->aabb.x_max * a->scale.array[0][0];
		a_x_max_tmp.y=0;
		a_x_max_tmp.z=0;
	tt_vec3 a_x_min_tmp;
		a_x_min_tmp.x=a->aabb.x_min * a->scale.array[0][0];
		a_x_min_tmp.y=0;
		a_x_min_tmp.z=0;
	tt_vec3 a_y_max_tmp;
		a_y_max_tmp.x=0;
		a_y_max_tmp.y=a->aabb.y_max * a->scale.array[1][1];
		a_y_max_tmp.z=0;
	tt_vec3 a_y_min_tmp;
		a_y_min_tmp.x=0;
		a_y_min_tmp.y=a->aabb.y_min * a->scale.array[1][1];
		a_y_min_tmp.z=0;
	tt_vec3 a_z_max_tmp;
		a_z_max_tmp.x=0;
		a_z_max_tmp.y=0;
		a_z_max_tmp.z=a->aabb.z_max * a->scale.array[2][2];
	tt_vec3 a_z_min_tmp;
		a_z_min_tmp.x=0;
		a_z_min_tmp.y=0;
		a_z_min_tmp.z=a->aabb.z_min * a->scale.array[2][2];

	//object b
	tt_vec3 b_x_max_tmp;
		b_x_max_tmp.x=b->aabb.x_max * b->scale.array[0][0];
		b_x_max_tmp.y=0;
		b_x_max_tmp.z=0;
	tt_vec3 b_x_min_tmp;
		b_x_min_tmp.x=b->aabb.x_min * b->scale.array[0][0];
		b_x_min_tmp.y=0;
		b_x_min_tmp.z=0;
	tt_vec3 b_y_max_tmp;
		b_y_max_tmp.x=0;
		b_y_max_tmp.y=b->aabb.y_max * b->scale.array[1][1];
		b_y_max_tmp.z=0;
	tt_vec3 b_y_min_tmp;
		b_y_min_tmp.x=0;
		b_y_min_tmp.y=b->aabb.y_min * b->scale.array[1][1];
		b_y_min_tmp.z=0;
	tt_vec3 b_z_max_tmp;
		b_z_max_tmp.x=0;
		b_z_max_tmp.y=0;
		b_z_max_tmp.z=b->aabb.z_max * b->scale.array[2][2];
	tt_vec3 b_z_min_tmp;
		b_z_min_tmp.x=0;
		b_z_min_tmp.y=0;
		b_z_min_tmp.z=b->aabb.z_min * b->scale.array[2][2];

	//rotation
	tt_mat3 a_rot=tt_math_mat4_crop_to_mat3(&a->rotation);
	tt_mat3 b_rot=tt_math_mat4_crop_to_mat3(&b->rotation);

	//object a
	a_x_max_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_x_max_tmp);
	a_x_min_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_x_min_tmp);
	a_y_max_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_y_max_tmp);
	a_y_min_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_y_min_tmp);
	a_z_max_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_z_max_tmp);
	a_z_min_tmp=tt_math_mat3_mul_vec3(&a_rot, &a_z_min_tmp);

	//object b
	b_x_max_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_x_max_tmp);
	b_x_min_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_x_min_tmp);
	b_y_max_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_y_max_tmp);
	b_y_min_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_y_min_tmp);
	b_z_max_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_z_max_tmp);
	b_z_min_tmp=tt_math_mat3_mul_vec3(&b_rot, &b_z_min_tmp);


	//getting the new extreme values for the aabb after the rotation
	//object a
	tt_vec3 a_max;
		//x max
		a_max.x=tt_helper_aabb_select_new_extreme_max(
			a_x_max_tmp.x,
			a_x_min_tmp.x,
			a_y_max_tmp.x,
			a_y_min_tmp.x,
			a_z_max_tmp.x,
			a_z_min_tmp.x);

		//y max
		a_max.y=tt_helper_aabb_select_new_extreme_max(
			a_x_max_tmp.y,
			a_x_min_tmp.y,
			a_y_max_tmp.y,
			a_y_min_tmp.y,
			a_z_max_tmp.y,
			a_z_min_tmp.y);

		//z max
		a_max.z=tt_helper_aabb_select_new_extreme_max(
			a_x_max_tmp.z,
			a_x_min_tmp.z,
			a_y_max_tmp.z,
			a_y_min_tmp.z,
			a_z_max_tmp.z,
			a_z_min_tmp.z);

	tt_vec3 a_min;
		//x min
		a_min.x=tt_helper_aabb_select_new_extreme_min(
			a_x_max_tmp.x,
			a_x_min_tmp.x,
			a_y_max_tmp.x,
			a_y_min_tmp.x,
			a_z_max_tmp.x,
			a_z_min_tmp.x);

		//y min
		a_min.y=tt_helper_aabb_select_new_extreme_min(
			a_x_max_tmp.y,
			a_x_min_tmp.y,
			a_y_max_tmp.y,
			a_y_min_tmp.y,
			a_z_max_tmp.y,
			a_z_min_tmp.y);

		//z min
		a_min.z=tt_helper_aabb_select_new_extreme_min(
			a_x_max_tmp.z,
			a_x_min_tmp.z,
			a_y_max_tmp.z,
			a_y_min_tmp.z,
			a_z_max_tmp.z,
			a_z_min_tmp.z);

	//object b
	tt_vec3 b_max;
		//x max
		b_max.x=tt_helper_aabb_select_new_extreme_max(
			b_x_max_tmp.x,
			b_x_min_tmp.x,
			b_y_max_tmp.x,
			b_y_min_tmp.x,
			b_z_max_tmp.x,
			b_z_min_tmp.x);

		//y max
		b_max.y=tt_helper_aabb_select_new_extreme_max(
			b_x_max_tmp.y,
			b_x_min_tmp.y,
			b_y_max_tmp.y,
			b_y_min_tmp.y,
			b_z_max_tmp.y,
			b_z_min_tmp.y);

		//z max
		b_max.z=tt_helper_aabb_select_new_extreme_max(
			b_x_max_tmp.z,
			b_x_min_tmp.z,
			b_y_max_tmp.z,
			b_y_min_tmp.z,
			b_z_max_tmp.z,
			b_z_min_tmp.z);

	tt_vec3 b_min;
		//x min
		b_min.x=tt_helper_aabb_select_new_extreme_min(
			b_x_max_tmp.x,
			b_x_min_tmp.x,
			b_y_max_tmp.x,
			b_y_min_tmp.x,
			b_z_max_tmp.x,
			b_z_min_tmp.x);

		//y min
		b_min.y=tt_helper_aabb_select_new_extreme_min(
			b_x_max_tmp.y,
			b_x_min_tmp.y,
			b_y_max_tmp.y,
			b_y_min_tmp.y,
			b_z_max_tmp.y,
			b_z_min_tmp.y);

		//z min
		b_min.z=tt_helper_aabb_select_new_extreme_min(
			b_x_max_tmp.z,
			b_x_min_tmp.z,
			b_y_max_tmp.z,
			b_y_min_tmp.z,
			b_z_max_tmp.z,
			b_z_min_tmp.z);

	//translation
	//object a
	a_max.x+=a->translation.array[3][0];
	a_max.y+=a->translation.array[3][1];
	a_max.z+=a->translation.array[3][2];

	a_min.x+=a->translation.array[3][0];
	a_min.y+=a->translation.array[3][1];
	a_min.z+=a->translation.array[3][2];

	//object b
	b_max.x+=b->translation.array[3][0];
	b_max.y+=b->translation.array[3][1];
	b_max.z+=b->translation.array[3][2];

	b_min.x+=b->translation.array[3][0];
	b_min.y+=b->translation.array[3][1];
	b_min.z+=b->translation.array[3][2];

	//checking for collision
	bool out=false;
	if(	a_min.x <= b_max.x &&
		a_max.x >= b_min.x &&
		a_min.y <= b_max.y &&
		a_max.y >= b_min.y &&
		a_min.z <= b_max.z &&
		a_max.z >= b_min.z)
	{
		out=true;
	}

	return out;
}

/*

	x_max=1,0,0;
	x_min=-1,0,0;
	y_max=0,1,0;
	y_min=0,-1,0;
*/