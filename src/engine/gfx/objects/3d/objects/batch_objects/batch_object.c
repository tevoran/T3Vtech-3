#include <tt.h>


tt_3d_batch_object* tt_3d_batch_object_new()
{
	tt_3d_batch_object *new_batch_object=malloc(sizeof(tt_3d_batch_object));
	if(!new_batch_object)
	{
		printf("[ERROR] couldn't create a new batch render object\n");
		return NULL;
	}

	//setting default values
	new_batch_object->vao=0;
	new_batch_object->vbo=0;
	new_batch_object->ibo=0;
	new_batch_object->num_verts=0;
	new_batch_object->num_indices=0;
	new_batch_object->vertex_data=NULL;
	new_batch_object->index_data=NULL;
	return new_batch_object;
}

void tt_3d_batch_object_batch_custom_model_objects(
	tt_3d_batch_object *batch_object,
	tt_3d_custom_model *model,
	unsigned int num,
	tt_3d_object **object)
{
	tt_vertex *vertex_base=(tt_vertex*)model->vertex_data;
	tt_vertex vertex_rot_and_scaled;
	tt_vertex vertex_translated;
	tt_vertex *vertex_out=malloc(
		num * model->num_verts * sizeof(tt_vertex));

	GLuint *base_index=model->index_data;
	GLuint *index_out=malloc(
		num * model->num_indices * sizeof(GLuint));

	//looking for highest index value
	GLuint max_index=0;
	for(int i=0; i<model->num_indices; i++)
	{
		if(base_index[i]>max_index)
		{
			max_index=base_index[i];
		}
	}
	max_index++;

	//calculating the mesh data
	for(int i=0; i<num; i++)
	{

		tt_mat3 mat_rotation=tt_math_mat4_crop_to_mat3(&object[i]->rotation);
		tt_mat3 mat_scale=tt_math_mat4_crop_to_mat3(&object[i]->scale);
		tt_mat3 mat_rot_and_scale=tt_math_mat3_mul(&mat_rotation, &mat_scale);
		tt_vec3 vec_translation=(tt_vec3) 
		{
			object[i]->translation.array[3][0],
			object[i]->translation.array[3][1],
			object[i]->translation.array[3][2],
		};

		//vertices
		for(int j=0; j<model->num_verts; j++)
		{
			//taking texture coordinates and normals to the end
			vertex_translated.tex=vertex_base[j].tex;

			//rotation and scaling
			vertex_rot_and_scaled.pos=tt_math_mat3_mul_vec3(&mat_rot_and_scale, &vertex_base[j].pos);
			vertex_rot_and_scaled.normal=tt_math_mat3_mul_vec3(&mat_rotation, &vertex_base[j].normal);

			//translation
			vertex_translated.pos=tt_math_vec3_add(&vec_translation, &vertex_rot_and_scaled.pos);
			vertex_translated.normal=vertex_rot_and_scaled.normal;

			//save vertex
			vertex_out[i * model->num_verts + j]=vertex_translated;
		}

		//indices
		for(int j=0; j<model->num_indices; j++)
		{
			index_out[i * model->num_indices + j] = base_index[j] + i * max_index ;
		}
	}


	batch_object->vertex_data=(GLfloat*)vertex_out;
	batch_object->index_data=index_out;
	batch_object->num_verts=num * model->num_verts;
	batch_object->num_indices=num * model->num_indices;

	//doing the necessary OpenGL stuff
	glGenVertexArrays(1, &batch_object->vao);
	glBindVertexArray(batch_object->vao);
	glGenBuffers(1, &batch_object->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, batch_object->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(tt_vertex) * batch_object->num_verts, 
		batch_object->vertex_data, 
		GL_STATIC_DRAW);
	glGenBuffers(1, &batch_object->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch_object->ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(GLuint) * batch_object->num_indices,
		batch_object->index_data,
		GL_STATIC_DRAW);
}

void tt_3d_batch_object_delete(tt_3d_batch_object **batch_object)
{
	if(*batch_object==NULL)
	{
		return;
	}

	if((*batch_object)->vertex_data)
	{
		free((*batch_object)->vertex_data);
	}
	if((*batch_object)->index_data)
	{
		free((*batch_object)->index_data);
	}

	free(*batch_object);
	*batch_object=NULL;
}
