#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

tt_3d_object* tt_new_quad(tt_vec3 pos, tt_vec3 orientation)
{
	//quad model data
	GLfloat quad[]=
	{
		pos.x, pos.y, pos.z,
		pos.x, pos.y + orientation.y, pos.z,
		pos.x + orientation.x, pos.y, pos.z + orientation.z,
		pos.x + orientation.x, pos.y + orientation.y, pos.z + orientation.z,
	};

	GLuint quad_indices[]=
	{
		0,1,2,
		1,2,3,
	};

	//creating the 3d object and putting it into the render list
	tt_3d_object *new_object=malloc(sizeof(tt_3d_object));
	new_object->node=tt_list_new_node(tt_3d_list_entry_node);
	if(!tt_3d_list_entry_node) //save the entry node if it's one
	{
		tt_3d_list_entry_node=new_object->node;
	}
	tt_list_node_set_data(new_object->node, new_object);
	new_object->num_verts=6; //it is a quad, it has 6 vertices

	//OpenGL stuff
	glGenVertexArrays(1, &new_object->vao);
	glBindVertexArray(new_object->vao);
	glGenBuffers(1, &new_object->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, new_object->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glGenBuffers(1, &new_object->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_object->ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(quad_indices),
		quad_indices,
		GL_STATIC_DRAW);

	return new_object;
}