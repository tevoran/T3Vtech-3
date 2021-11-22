#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

GLfloat quad[]=
{
	-1.0, -1.0, 0.0,
	1.0, -1.0, 0.0,
	-1.0, 1.0, 0.0,

	-1.0, 1.0, 0.0,
	1.0, -1.0, 0.0,
	1.0, 1.0, 0.0,
};

tt_3d_object* tt_new_quad()
{
	tt_3d_object *new_object=malloc(sizeof(tt_3d_object));
	new_object->node=tt_list_new_node(tt_3d_list_entry_node);
	if(!tt_3d_list_entry_node) //save the entry node if it's one
	{
		tt_3d_list_entry_node=new_object->node;
	}
	tt_list_node_set_data(new_object->node, new_object);

	glGenVertexArrays(1, &new_object->vao);
	glBindVertexArray(new_object->vao);
	glGenBuffers(1, &new_object->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, new_object->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
}