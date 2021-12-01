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
	tt_mat4 translation;
	tt_mat4 scale;
	tt_mat4 rotation;

	//properties
	GLuint texture;

} typedef tt_3d_object;

#include "custom_models/custom_model.h"

//preparation functions
void tt_gfx_prepare_quad();

//3D object related
tt_3d_object* tt_3d_object_new();
void tt_3d_object_make_quad(tt_3d_object *object);
void tt_3d_object_delete(tt_3d_object **object);

//transformations
void tt_3d_object_scale(tt_3d_object *object, tt_vec3 *scale);
void tt_3d_object_set_position(tt_3d_object *object, tt_vec3 *position);
void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians);

//object properties
void tt_3d_object_use_texture(tt_3d_object *object, tt_3d_texture *texture);
void tt_3d_object_use_default_texture(tt_3d_object *object);

#endif