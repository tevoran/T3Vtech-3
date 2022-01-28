#include <tt.h>

extern GLuint tt_gfx_2d_sprite_vao;
extern GLuint tt_gfx_2d_sprite_vbo;
extern GLuint tt_gfx_2d_sprite_ibo;

//render list
//used once per frame

tt_2d_object* tt_2d_object_new()
{
	tt_2d_object *new_object=malloc(sizeof(tt_2d_object));


	//set default parameters
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;
	new_object->num_indices=0;

	return new_object;
}

void tt_2d_object_render(tt_2d_object *object)
{

}