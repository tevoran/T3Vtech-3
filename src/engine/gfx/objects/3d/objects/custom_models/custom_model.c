#include <tt.h>


tt_3d_custom_model* tt_3d_custom_model_load_file(const char *path)
{
	int num_verts;
	int num_indices;
	GLfloat *vertex_data;
	GLuint *index_data;
	tt_3d_collision_aabb aabb;

	//deciding the file type
	//OBJ
	if(strstr(path, ".obj") || strstr(path, ".OBJ"))
	{

		if(!tt_3d_object_custom_model_load_obj_file(
			path, 
			&num_verts,
			&num_indices,
			&vertex_data, 
			&index_data,
			&aabb))
		{
			return NULL;
		}
		else
		{
			tt_log(TT_INFO, "OBJ model from %s successfully loaded", path);
		}
	}
	else
	{
		return NULL;
	}

	//creating the custom model
	tt_3d_custom_model *model=malloc(sizeof(tt_3d_custom_model));
	if(!model)
	{
		tt_log(TT_ERROR, "memory couldn't be allocated for a custom 3D model");
		return NULL;
	}
	//saving data to the custom object's struct
	model->num_verts=num_verts;
	model->num_indices=num_indices;
	model->vertex_data=vertex_data;
	model->index_data=index_data;
	model->bounding_sphere_radius=tt_3d_aabb_get_radius(&aabb);
	model->aabb=aabb;

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(tt_3d_custom_model_vertex)*num_verts, 
		vertex_data, 
		GL_STATIC_DRAW);
	glGenBuffers(1, &model->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLuint)*num_indices,
		index_data,
		GL_STATIC_DRAW);

	return model;
}


void tt_3d_custom_model_delete(tt_3d_custom_model **model)
{
	if(*model == NULL)
	{
		return;
	}
	
	free((*model)->vertex_data);
	free((*model)->index_data);

	glDeleteVertexArrays(1, &(*model)->vao);
	glDeleteBuffers(1, &(*model)->vbo);
	glDeleteBuffers(1, &(*model)->ibo);

	*model=NULL; //mark the custom model as deleted
}
