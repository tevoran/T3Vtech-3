#include <tt.h>

struct vertex
{
	tt_vec3 pos;
	tt_vec2 tex_coord;
} typedef vertex;

tt_3d_custom_model* tt_3d_custom_model_load_file(const char *path)
{
	int num_verts;
	int num_indices;
	GLfloat *vertex_data;
	GLuint *index_data;

	//deciding the file type
	//OBJ
	if(strstr(path, ".obj") || strstr(path, ".OBJ"))
	{

		if(!tt_3d_object_custom_model_load_obj_file(
			path, 
			&num_verts,
			&num_indices,
			&vertex_data, 
			&index_data))
		{
			return NULL;
		}
		else
		{
			printf("OBJ model from %s successfully loaded\n", path);
		}
	}

	//creating the custom model
	tt_3d_custom_model *model=malloc(sizeof(tt_3d_custom_model));
	model->num_verts=num_verts;
	model->num_indices=num_indices;

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*num_verts, vertex_data, GL_STATIC_DRAW);
	glGenBuffers(1, &model->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLuint)*num_indices,
		index_data,
		GL_STATIC_DRAW);

	free(vertex_data);
	free(index_data);

	return model;
}


void tt_3d_custom_model_delete(tt_3d_custom_model **model)
{
	glDeleteVertexArrays(1, &(*model)->vao);
	glDeleteBuffers(1, &(*model)->vbo);
	glDeleteBuffers(1, &(*model)->ibo);

	*model=NULL; //mark the custom model as deleted
}
