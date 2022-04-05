#include <tt.h>

void tt_3d_object_use_custom_model(tt_3d_object *object, tt_3d_custom_model *model)
{
	if(model) //use model only if it exists
	{
		object->vao=model->vao;
		object->vbo=model->vbo;
		object->ibo=model->ibo;
		object->num_indices=model->num_indices;	
		object->bounding_sphere_radius=model->bounding_sphere_radius;
		object->aabb=model->aabb;

		//actual image data
		object->vertex_data=model->vertex_data;
		object->index_data=model->index_data;
	}
}