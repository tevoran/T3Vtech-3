#ifndef TT_GFX_OBJECTS_2D_H
#define TT_GFX_OBJECTS_2D_H


struct tt_2d_object
{
	//OpenGL relevant data
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_indices;

} typedef tt_2d_object;

void tt_gfx_prepare_sprite();

tt_2d_object* tt_2d_object_new();

//sprite
void tt_2d_object_make_sprite(tt_2d_object *object);

#endif