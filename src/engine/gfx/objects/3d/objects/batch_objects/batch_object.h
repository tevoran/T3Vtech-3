#ifndef TT_GFX_OBJECTS_3D_BATCH_OBJECT_H
#define TT_GFX_OBJECTS_3D_BATCH_OBJECT_H

#include <tt.h>
#include "../custom_models/custom_model.h"

//vertex format pos, pos, pos, tex, tex, normal, normal, normal is expected

struct tt_3d_batch_object
{
	//opengl stuff
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	uint32_t num_verts;
	uint32_t num_indices;

	//actual model data
	GLfloat *vertex_data;
	GLuint *index_data;

} typedef tt_3d_batch_object;

tt_3d_batch_object* tt_3d_batch_object_new();
void tt_3d_batch_object_batch_custom_model_objects(
	tt_3d_batch_object *batch_object,
	tt_3d_custom_model *model,
	unsigned int num,
	tt_3d_object **object);
void tt_3d_batch_object_delete(tt_3d_batch_object **batch_object);

#endif