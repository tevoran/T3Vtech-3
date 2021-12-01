#ifndef TT_GFX_OBJECTS_3D_CUSTOM_MODEL_OBJ_H
#define TT_GFX_OBJECTS_3D_CUSTOM_MODEL_OBJ_H

#include <tt.h>

//returns true on success
bool tt_3d_object_custom_model_load_obj_file(
	const char *path,
	int *num_vertices);
#endif