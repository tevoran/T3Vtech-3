#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

extern GLuint tt_gfx_3d_default_tex; //default texture

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

//getting object properties
float tt_3d_object_get_bounding_sphere_size(tt_3d_object *object)
{
	return object->size_bounding_sphere;
}
