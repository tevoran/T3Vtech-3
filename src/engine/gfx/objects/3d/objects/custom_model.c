#include <tt.h>

void tt_3d_object_use_custom_model(tt_3d_object *object, tt_3d_custom_model *model)
{
	object->vao=model->vao;
	object->vbo=model->vbo;
	object->ibo=model->ibo;
	object->num_indices=model->num_indices;
}