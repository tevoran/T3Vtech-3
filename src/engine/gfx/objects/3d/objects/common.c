#include <tt.h>

#include <float.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

extern GLuint tt_gfx_3d_default_tex; //default texture

//helper functions
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
	new_object->num_verts=0;
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;

	tt_math_mat4_make_identity_matrix(&new_object->translation);
	tt_math_mat4_make_identity_matrix(&new_object->scale);
	tt_math_mat4_make_identity_matrix(&new_object->rotation);

	new_object->texture=tt_gfx_3d_default_tex;
	new_object->lighting_affected=true;
	new_object->point_light_count=0;
	new_object->ao_light_count=0;
	new_object->bounding_sphere_radius=0;
	new_object->invisibility_toggle=false; //make visible by default
	new_object->backface_culling_toggle=true; //enable backface culling for the object

	new_object->color = (tt_vec3){ 1.0f, 1.0f, 1.0f };
	new_object->emission = (tt_vec3){ 0.0f, 0.0f, 0.0f };

	//actual model data
	new_object->vertex_data=NULL;
	new_object->index_data=NULL;

	//setting the aabb to defaults
	new_object->aabb.max = (tt_vec3){ 0, 0, 0 };
	new_object->aabb.min = (tt_vec3){ 0, 0, 0 };

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
	object->translation.array[0][3]=position->x;
	object->translation.array[1][3]=position->y;
	object->translation.array[2][3]=position->z;
}

void tt_3d_object_set_rotation(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
{
	object->rotation = tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
}

void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
{
	tt_mat4 rot_delta_mat=tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
	object->rotation=tt_math_mat4_mul(&rot_delta_mat, &object->rotation);
}

void tt_3d_object_rotate_local_axis(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
{
	tt_mat4 rot_delta_mat = tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
	object->rotation = tt_math_mat4_mul(&object->rotation, &rot_delta_mat);
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

void tt_3d_object_set_color(tt_3d_object *object, tt_vec3 *color)
{
	object->color = *color;
}

void tt_3d_object_set_emission(tt_3d_object *object, tt_vec3 *emission)
{
	object->emission = *emission;
}

void tt_3d_object_light_affected(tt_3d_object *object, bool toggle)
{
	object->lighting_affected=toggle;
}

void tt_3d_object_add_point_light(tt_3d_object *object, tt_point_light light)
{
	if(object->point_light_count>=MAX_POINT_LIGHTS_PER_OBJECT)
	{
		return;
	}

	object->point_lights[object->point_light_count++] = light;
}

void tt_3d_object_remove_point_light(tt_3d_object *object, tt_point_light light)
{
	for(int i=0; i<object->point_light_count; ++i)
	{
		if (object->point_lights[i] == light)
		{
			object->point_lights[i] = object->point_lights[object->point_light_count - 1];

			--i;
			--object->point_light_count;
		}
	}
}

void tt_3d_object_clear_point_lights(tt_3d_object *object)
{
	object->point_light_count = 0;
}

int tt_3d_object_get_point_light_count(tt_3d_object *object)
{
	return object->point_light_count;
}

void tt_3d_object_add_ao_light(tt_3d_object *object, tt_ao_light light)
{
	if (object->ao_light_count>=MAX_AO_LIGHTS_PER_OBJECT)
	{
		return;
	}

	object->ao_lights[object->ao_light_count++] = light;
}

void tt_3d_object_remove_ao_light(tt_3d_object *object, tt_ao_light light)
{
	for (int i = 0; i<object->ao_light_count; ++i)
	{
		if (object->ao_lights[i]==light)
		{
			object->ao_lights[i] = object->ao_lights[object->ao_light_count - 1];

			--i;
			--object->ao_light_count;
		}
	}
}

void tt_3d_object_clear_ao_lights(tt_3d_object *object)
{
	object->ao_light_count = 0;
}

int tt_3d_object_get_ao_light_count(tt_3d_object *object)
{
	return object->ao_light_count;
}

void tt_3d_object_make_invisible(tt_3d_object *object, bool toggle)
{
	object->invisibility_toggle=toggle;
}

void tt_3d_object_back_face_culling(tt_3d_object *object, bool toggle)
{
	object->backface_culling_toggle=toggle;	
}

//getting object properties
float tt_3d_object_get_bounding_sphere_size(tt_3d_object *object)
{
	return object->bounding_sphere_radius;
}

void tt_3d_aabb_after_world_transform(tt_3d_object *obj, tt_3d_collision_aabb *aabb) {
	tt_vec3 vertices[8];
	const tt_vec3 bounds[2] = { obj->aabb.min, obj->aabb.max };
	for (int i=0; i<2; ++i)
	{
		for (int j=0; j<2; ++j)
		{
			for (int k=0; k<2; ++k)
			{
				vertices[i*4+j*2+k*1].x = bounds[i].x;
				vertices[i*4+j*2+k*1].y = bounds[j].y;
				vertices[i*4+j*2+k*1].z = bounds[k].z;
			}
		}
	}

	tt_vec3 scale = (tt_vec3)
	{
		obj->scale.array[0][0],
		obj->scale.array[1][1],
		obj->scale.array[2][2],
	};

	tt_vec3 translation = (tt_vec3)
	{
		obj->translation.array[0][3],
		obj->translation.array[1][3],
		obj->translation.array[2][3]
	};

	tt_mat3 rotation = tt_math_mat4_crop_to_mat3(&obj->rotation);

	aabb->min = (tt_vec3){ FLT_MAX, FLT_MAX, FLT_MAX };
	aabb->max = (tt_vec3){ -FLT_MAX, -FLT_MAX, -FLT_MAX };

	for (int i=0; i<8; ++i)
	{
		vertices[i] = tt_math_vec3_mul(&vertices[i], &scale);
		vertices[i] = tt_math_mat3_mul_vec3(&rotation, &vertices[i]);
		vertices[i] = tt_math_vec3_add(&vertices[i], &translation);

		aabb->min = tt_math_vec3_min(&aabb->min, &vertices[i]);
		aabb->max = tt_math_vec3_max(&aabb->max, &vertices[i]);
	}
}

//collisions
bool tt_3d_object_colliding_aabb(tt_3d_object *a, tt_3d_object *b)
{
	tt_3d_collision_aabb a_aabb, b_aabb;
	tt_3d_aabb_after_world_transform(a, &a_aabb);
	tt_3d_aabb_after_world_transform(b, &b_aabb);

	return a_aabb.max.x >= b_aabb.min.x
		&& a_aabb.min.x <= b_aabb.max.x
		&& a_aabb.max.y >= b_aabb.min.y
		&& a_aabb.min.y <= b_aabb.max.y
		&& a_aabb.max.z >= b_aabb.min.z
		&& a_aabb.min.z <= b_aabb.max.z;
}
