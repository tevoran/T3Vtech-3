#include <tt.h>

extern GLuint tt_gfx_2d_sprite_vao;
extern GLuint tt_gfx_2d_sprite_vbo;
extern GLuint tt_gfx_2d_sprite_ibo;

void tt_gfx_prepare_sprite()
{
	//quad model data
	GLfloat sprite[]=
	{
		0.0, 0.0,		0.0, 1.0, 
		0.0, -1.0,		0.0, 0.0,
		1.0, 0.0,		1.0, 1.0,
		1.0, -1.0,		1.0, 0.0,
	};

	GLuint sprite_indices[]=
	{
		0,1,2,
		1,2,3,
	};

	//create the OpenGL IDs
	glGenVertexArrays(1, &tt_gfx_2d_sprite_vao);
	glBindVertexArray(tt_gfx_2d_sprite_vao);
	glGenBuffers(1, &tt_gfx_2d_sprite_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tt_gfx_2d_sprite_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);
	glGenBuffers(1, &tt_gfx_2d_sprite_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tt_gfx_2d_sprite_ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(sprite_indices),
		sprite_indices,
		GL_STATIC_DRAW);
}

void tt_2d_object_make_sprite(tt_2d_object *object)
{
	object->vao=tt_gfx_2d_sprite_vao;
	object->vbo=tt_gfx_2d_sprite_vbo;
	object->ibo=tt_gfx_2d_sprite_ibo;
	object->num_indices=6; //has 4 vertices and 6 total indices
}
