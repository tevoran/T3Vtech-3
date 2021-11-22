#ifndef TT_GFX_OBJECTS_3D_H
#define TT_GFX_OBJECTS_3D_H

#include <tt.h>

//all 3D objects are organized in a linked list that the render goes through
struct tt_3d_object
{
	tt_node *node; //pointer to a node that points also back to the object

	//OpenGL relevant data
	GLuint vao;
	GLuint vbo;
} typedef tt_3d_object;


tt_3d_object* tt_new_quad();

#endif