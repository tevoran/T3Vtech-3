#include <tt.h>

void tt_3d_object_use_batch_object(tt_3d_object *object, tt_3d_batch_object *batch_object)
{
	if(!object || !batch_object)
	{
		tt_log(TT_ERROR, "no 3D object or batch object is available");
		return;
	}

	object->vao=batch_object->vao;
	object->vbo=batch_object->vbo;
	object->ibo=batch_object->ibo;
	object->num_verts=batch_object->num_verts;
	object->num_indices=batch_object->num_indices;	
	object->bounding_sphere_radius=batch_object->bounding_sphere_radius;
	//object->aabb=batch_object->aabb;
}

