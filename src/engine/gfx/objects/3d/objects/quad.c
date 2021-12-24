#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

//the quad preparation OpenGL ID
extern GLuint tt_gfx_3d_quad_vao;
extern GLuint tt_gfx_3d_quad_vbo;
extern GLuint tt_gfx_3d_quad_ibo;

void tt_gfx_prepare_quad()
{
	//quad model data
	GLfloat quad[]=
	{
		-0.5, -0.5, 0.0,	0.0, 0.0,	0.0, 0.0, -1.0, 
		-0.5, 0.5, 0.0,		0.0, 1.0,	0.0, 0.0, -1.0,
		0.5, -0.5, 0.0,		1.0, 0.0,	0.0, 0.0, -1.0,
		0.5, 0.5, 0.0,		1.0, 1.0,	0.0, 0.0, -1.0,
	};

	GLuint quad_indices[]=
	{
		0,1,2,
		1,2,3,
	};

	//create the OpenGL IDs
	glGenVertexArrays(1, &tt_gfx_3d_quad_vao);
	glBindVertexArray(tt_gfx_3d_quad_vao);
	glGenBuffers(1, &tt_gfx_3d_quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tt_gfx_3d_quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glGenBuffers(1, &tt_gfx_3d_quad_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tt_gfx_3d_quad_ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(quad_indices),
		quad_indices,
		GL_STATIC_DRAW);
}

void tt_gfx_cleanup_quad()
{
	glDeleteVertexArrays(1, &tt_gfx_3d_quad_vao);
	glDeleteBuffers(1, &tt_gfx_3d_quad_vbo);
	glDeleteBuffers(1, &tt_gfx_3d_quad_ibo);
}

void tt_3d_object_make_quad(tt_3d_object *object)
{
	object->num_indices=6; //it is a quad, it has 6 vertices
	object->vao=tt_gfx_3d_quad_vao;
	object->vbo=tt_gfx_3d_quad_vbo;
	object->ibo=tt_gfx_3d_quad_ibo;
	object->size_bounding_sphere=1.0; //diameter is 1.0
}