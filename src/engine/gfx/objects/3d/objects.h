#ifndef TT_GFX_OBJECTS_3D_H
#define TT_GFX_OBJECTS_3D_H

#include <tt.h>

//all 3D objects are organized in a linked list that the render goes through
struct tt_3d_object
{
	//pointer to a node in the render list that points also back to the object
	tt_node *node;

	//OpenGL relevant data
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_verts;

	//transformations
	float translation[4][4];
	float scale[4][4];
	float rotation[4][4];

} typedef tt_3d_object;

//preparation functions
void tt_gfx_prepare_quad();


tt_3d_object* tt_3d_object_new();
void tt_3d_object_make_quad(tt_3d_object *object);
void tt_3d_object_delete(tt_3d_object **object);

#endif