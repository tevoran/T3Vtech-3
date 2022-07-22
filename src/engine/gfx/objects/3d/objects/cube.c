#include <tt.h>

//this is the beginning of the 3D object rendering list
extern T_node *tt_3d_list_entry_node;

//the cube preparation OpenGL ID
extern GLuint tt_gfx_3d_cube_vao;
extern GLuint tt_gfx_3d_cube_vbo;
extern GLuint tt_gfx_3d_cube_ibo;

void tt_gfx_prepare_cube()
{
	//quad model data
	GLfloat cube[]=
	{
		//front face
		-0.5, -0.5, -0.5,	0.0, 0.0,	0.0, 0.0, -1.0,
		-0.5, 0.5, -0.5,	0.0, 1.0,	0.0, 0.0, -1.0,
		0.5, -0.5, -0.5,	1.0, 0.0,	0.0, 0.0, -1.0,
		0.5, 0.5, -0.5,		1.0, 1.0,	0.0, 0.0, -1.0,

		//back face
		-0.5, -0.5, 0.5,	0.0, 0.0,	0.0, 0.0, 1.0,
		-0.5, 0.5, 0.5,		0.0, 1.0,	0.0, 0.0, 1.0,
		0.5, -0.5, 0.5,		1.0, 0.0,	0.0, 0.0, 1.0,
		0.5, 0.5, 0.5,		1.0, 1.0,	0.0, 0.0, 1.0,

		//left face
		-0.5, -0.5, 0.5,	0.0, 0.0,	-1.0, 0.0, 0.0,
		-0.5, 0.5, 0.5,		0.0, 1.0,	-1.0, 0.0, 0.0,
		-0.5, -0.5, -0.5,	1.0, 0.0,	-1.0, 0.0, 0.0,
		-0.5, 0.5, -0.5,	1.0, 1.0,	-1.0, 0.0, 0.0,

		//right face
		0.5, -0.5, 0.5,		0.0, 0.0,	1.0, 0.0, 0.0,
		0.5, 0.5, 0.5,		0.0, 1.0,	1.0, 0.0, 0.0,
		0.5, -0.5, -0.5,	1.0, 0.0,	1.0, 0.0, 0.0,
		0.5, 0.5, -0.5,		1.0, 1.0,	1.0, 0.0, 0.0,

		//top face
		-0.5, 0.5, -0.5,	0.0, 0.0,	0.0, 1.0, 0.0,
		-0.5, 0.5, 0.5,		0.0, 1.0,	0.0, 1.0, 0.0,
		0.5, 0.5, -0.5,		1.0, 0.0,	0.0, 1.0, 0.0,
		0.5, 0.5, 0.5,		1.0, 1.0,	0.0, 1.0, 0.0,

		//bottom face
		-0.5, -0.5, -0.5,	0.0, 0.0,	0.0, -1.0, 0.0,
		-0.5, -0.5, 0.5,	0.0, 1.0,	0.0, -1.0, 0.0,
		0.5, -0.5, -0.5,	1.0, 0.0,	0.0, -1.0, 0.0,
		0.5, -0.5, 0.5,		1.0, 1.0,	0.0, -1.0, 0.0,
	};

	GLuint cube_indices[]=
	{
		//front face
		0,1,2,
		1,2,3,

		//back face
		4,5,6,
		5,6,7,

		//left face
		8,9,10,
		9,10,11,

		//right face
		12,13,14,
		13,14,15,

		//top face
		16,17,18,
		17,18,19,

		//bottom face
		20,21,22,
		21,22,23
	};

	//create the OpenGL IDs
	glGenVertexArrays(1, &tt_gfx_3d_cube_vao);
	glBindVertexArray(tt_gfx_3d_cube_vao);
	glGenBuffers(1, &tt_gfx_3d_cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tt_gfx_3d_cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glGenBuffers(1, &tt_gfx_3d_cube_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tt_gfx_3d_cube_ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(cube_indices),
		cube_indices,
		GL_STATIC_DRAW);
}

void tt_gfx_cleanup_cube()
{
	glDeleteVertexArrays(1, &tt_gfx_3d_cube_vao);
	glDeleteBuffers(1, &tt_gfx_3d_cube_vbo);
	glDeleteBuffers(1, &tt_gfx_3d_cube_ibo);
}

void tt_3d_object_make_cube(tt_3d_object *object)
{
	object->num_indices=36; //it is a quad, it has 6 vertices
	object->vao=tt_gfx_3d_cube_vao;
	object->vbo=tt_gfx_3d_cube_vbo;
	object->ibo=tt_gfx_3d_cube_ibo;

	//setting aabb
	object->aabb.max = (tt_vec3){ 0.5, 0.5, 0.5 };
	object->aabb.min = (tt_vec3){ -0.5, -0.5, -0.5 };

	object->bounding_sphere_radius = tt_3d_aabb_get_radius(&object->aabb);
}
