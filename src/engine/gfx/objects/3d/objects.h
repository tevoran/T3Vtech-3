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
	GLuint ibo;
	uint32_t num_verts;
} typedef tt_3d_object;


tt_3d_object* tt_new_quad(tt_vec3 pos, tt_vec3 orientation);
void tt_delete_3d_object(tt_3d_object **object);

#endif