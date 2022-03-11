#ifndef TT_GFX_OBJECTS_3D_CUSTOM_MODEL_H
#define TT_GFX_OBJECTS_3D_CUSTOM_MODEL_H

#include <tt.h>

//different file types
#include "obj.h"

struct tt_3d_custom_model_vertex
{
	tt_vec3 pos;
	tt_vec2 tex_coord;
	tt_vec3 normal;
} typedef tt_3d_custom_model_vertex;

struct tt_3d_custom_model
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_verts;
	uint32_t num_indices;

	//parameters
	float size_bounding_sphere;

	//collision properties
	tt_3d_collision_aabb aabb; //its measurements derive from the mesh itself
		//so it needs effectively transformed like the mesh itself to be usable

} typedef tt_3d_custom_model;

tt_3d_custom_model* tt_3d_custom_model_load_file(const char *path);
void tt_3d_custom_model_delete(tt_3d_custom_model **model);

#endif