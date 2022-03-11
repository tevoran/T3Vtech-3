#ifndef TT_GFX_OBJECTS_3D_CUSTOM_MODEL_OBJ_H
#define TT_GFX_OBJECTS_3D_CUSTOM_MODEL_OBJ_H

#include <tt.h>

//vertex and index data need to be free'd later when the model got onto
//the video memory
//returns true on success
bool tt_3d_object_custom_model_load_obj_file(
	const char *path,
	int *num_vertices,
	int *num_indices,
	GLfloat **vertex_data,
	GLuint **index_data,
	float *size_bounding_sphere,
	tt_3d_collision_aabb *aabb);
#endif