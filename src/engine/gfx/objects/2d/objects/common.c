#include <tt.h>

//prepared OpenGL IDs for a sprite
extern GLuint tt_gfx_2d_sprite_vao;
extern GLuint tt_gfx_2d_sprite_vbo;
extern GLuint tt_gfx_2d_sprite_ibo;

extern GLuint tt_gfx_2d_default_tex; //default texture

//render list
//used once per frame
extern tt_node *tt_2d_list_entry_node;
extern tt_node *tt_2d_list_last_entry;

tt_2d_object* tt_2d_object_new()
{
	tt_2d_object *new_object=malloc(sizeof(tt_2d_object));


	//set default parameters
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;
	new_object->num_indices=0;

	//transformations
	new_object->translation.x=0.0;
	new_object->translation.y=0.0;
	new_object->scale.x=1.0;
	new_object->scale.y=1.0;
	tt_math_mat2_make_identity_matrix(&new_object->rotation);

	//properties
	new_object->texture=tt_gfx_2d_default_tex;
	new_object->is_text_object=false;

	return new_object;
}

//the function uses a pointer pointer so that the deleted object pointer can
//be set to NULL. This is done to reduce possible segfaults by accidentally
//deleting the same object twice.
void tt_2d_object_delete(tt_2d_object **object)
{
	//if this object has already been deleted then just quit
	if(*object==NULL)
	{
		return; 
	}

	//delete the text texture if the object is a text object
	if((*object)->is_text_object)
	{
		glDeleteTextures(1, &(*object)->texture);
	}

	free(*object);
	*object=NULL; //mark object as deleted
}

//get the desired object into the 2D render list
//the object's adress get passed into the data section of tt_node
void tt_2d_object_render(tt_2d_object *object)
{
	//if the object is already deleted then simply return
	if(!object)
	{
		return;
	}

	tt_2d_list_last_entry=tt_list_new_node(tt_2d_list_last_entry);
	if(!tt_2d_list_last_entry)
	{
		printf("[ERROR] couldn't create a new entry to the 2D render list\n");
	}
	//if there is no node yet then use the newly created one as first one
	if(tt_2d_list_entry_node==NULL)
	{
		tt_2d_list_entry_node=tt_2d_list_last_entry;
	}
	tt_list_node_set_data(tt_2d_list_last_entry, object);
}


void tt_2d_object_clear_render_list()
{
	while(tt_2d_list_entry_node)
	{
		tt_list_remove_node(&tt_2d_list_entry_node);
	}
	tt_2d_list_last_entry=NULL;
}

void tt_2d_object_set_position(tt_2d_object *object, tt_vec2 *position)
{
	//if the object is already deleted then simply return
	if(!object)
	{
		return;
	}

	object->translation=*position;
}

void tt_2d_object_scale(tt_2d_object *object, tt_vec2 *scale)
{
	//if the object is already deleted then simply return
	if(!object)
	{
		return;
	}

	object->scale=*scale;
}

void tt_2d_object_rotate(tt_2d_object *object, float radians)
{
	//if the object is already deleted then simply return
	if(!object)
	{
		return;
	}

	object->rotation.array[0][0]=cos(radians);
	object->rotation.array[0][1]=-sin(radians);
	object->rotation.array[1][0]=sin(radians);
	object->rotation.array[1][1]=cos(radians);
}

void tt_2d_object_use_texture(tt_2d_object *object, tt_2d_texture *texture)
{
	//if the object is already deleted then simply return
	if(!object)
	{
		return;
	}
	
	if(texture) //use texture only if it exists
	{
		object->texture=texture->texture;
	}
	else //use default texture
	{
		object->texture=tt_gfx_2d_default_tex;
	}
}