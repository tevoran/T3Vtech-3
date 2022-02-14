#include <tt.h>

#define LINE_LENGTH 1024


//vertex and index data need to be free'd later when the model got onto
//the video memory
//returns true on success
bool tt_3d_object_custom_model_load_obj_file(
	const char *path,
	int *num_vertices,
	int *num_indices,
	GLfloat **vertex_data,
	GLuint **index_data,
	float *size_bounding_sphere)
{
	//outgoing variables
	*num_indices=0;
	*num_vertices=0;
	*size_bounding_sphere=0;

	//function intern variables
	int num_pos=0;
	int num_tex_coord=0;
	int num_normal=0;

	//used arrays for storing model file data
	tt_vec3 *pos_array=NULL;
	tt_vec2 *tex_array=NULL;
	tt_vec3 *normal_array=NULL;

	FILE *file=fopen(path, "r");
	if(!file)
	{
		printf("[ERROR] obj model couldn't be read from %s\n", path);
		return false;
	}

	//getting information about the file and the model
	{
		char line[LINE_LENGTH];
		while(fgets(line, LINE_LENGTH, file))
		{
			//counting vertex positions
			if(strstr(line, "v "))
			{
				num_pos++;
			}

			//counting texture coordinates
			if(strstr(line, "vt "))
			{
				num_tex_coord++;
			}

			//counting face normals
			if(strstr(line, "vn "))
			{
				num_normal++;
			}

			//counting number of vertices and indices
			if(strstr(line, "f "))
			{
				int num_vertices_in_face=0;
				char *token;
				token=strtok(line, " ");
				while(token)
				{
					int elem_read=0;
					float tmp_a, tmp_b, tmp_c;
					elem_read=sscanf(token, "%f/%f/%f", &tmp_a, &tmp_b, &tmp_c);
					//when face contains vertices count them
					if(elem_read>0)
					{
						num_vertices_in_face++;
					}
					token=strtok(NULL, " ");
				}

				*num_vertices+=num_vertices_in_face;
				*num_indices+=3*num_vertices_in_face-6;
			}
		}
	}

	//retrieving the data from the file
	{
		fseek(file, 0, SEEK_SET);

		//creating arrays for the model file data
		pos_array=malloc(sizeof(tt_vec3)*num_pos);
		tex_array=malloc(sizeof(tt_vec2)*num_tex_coord);
		normal_array=malloc(sizeof(tt_vec3)*num_normal);

		//creating arrays for model data that goes later to OpenGL
		*vertex_data=malloc(sizeof(tt_3d_custom_model_vertex)* (*num_vertices));
		*index_data=malloc(sizeof(GLuint)* (*num_indices));

		//loop variables
		char line[LINE_LENGTH];
		int i_pos=0;
		int i_tex=0;
		int i_normal=0;
		while(fgets(line, LINE_LENGTH, file))
		{
			//saving vertex position data into its array
			if(strstr(line, "v "))
			{
				tt_vec3 tmp;
				if(!sscanf(line, "v %f %f %f", &tmp.x, &tmp.y, &tmp.z))
				{
					printf("[ERROR] vertex position couldn't be processed in");
					printf(" OBJ file\n");
					return false;
				}

				pos_array[i_pos]=tmp;
				float tmp_length=tt_math_vec3_length(&pos_array[i_pos]);
				tmp_length*=2; //we need the diameter instead of the radius
				if(*size_bounding_sphere < tmp_length)
				{
					*size_bounding_sphere=tmp_length;
				}
				i_pos++;
			}

			//saving texture coordinates into their array
			if(strstr(line, "vt "))
			{
				tt_vec2 tmp;
				if(!sscanf(line, "vt %f %f", &tmp.x, &tmp.y))
				{
					printf("[ERROR] texture coordinates couldn't be processed");
					printf("in OBJ file\n");
					return false;
				}

				tex_array[i_tex]=tmp;
				i_tex++;
			}

			//saving vertex position data into its array
			if(strstr(line, "vn "))
			{
				tt_vec3 tmp;
				if(!sscanf(line, "vn %f %f %f", &tmp.x, &tmp.y, &tmp.z))
				{
					printf("[ERROR] vertex normals couldn't be processed in");
					printf(" OBJ file\n");
					return false;
				}

				normal_array[i_normal]=tmp;
				i_normal++;
			}
		};
	}

	//creating the model data that is suitable for OpenGL
	{
		fseek(file, 0, SEEK_SET);

		tt_3d_custom_model_vertex *vertex_array=
			(tt_3d_custom_model_vertex*)*vertex_data;
		int num_verts_done=0;
		int num_verts_pre_face=0;
		int num_indices_done=0;
		int i=0;

		char line[LINE_LENGTH];
		while(fgets(line, LINE_LENGTH, file))
		{
			//going through the face
			if(strstr(line, "f "))
			{
				char *token;
				token=strtok(line, " ");

				num_verts_pre_face=num_verts_done;

				//going through the different vertices of the face
				while(token)
				{
					int i_pos=0;
					int i_tex=0;
					int i_normal=0;

					int elem_read=0;
					elem_read=sscanf(token, "%i/%i/%i", &i_pos, &i_tex, &i_normal);
					if(elem_read>0)
					{
						i_pos--;
						i_tex--;
						i_normal--;

						tt_3d_custom_model_vertex tmp_vertex;
						tmp_vertex.pos=pos_array[i_pos];
						tmp_vertex.tex_coord=tex_array[i_tex];
						tmp_vertex.normal=normal_array[i_normal];

						vertex_array[num_verts_done]=tmp_vertex;
						num_verts_done++;
					}

					token=strtok(NULL, " ");
				}	

				//saving the indices
				int num_verts_face=num_verts_done-num_verts_pre_face;
				int num_indices_face=3*num_verts_face-6;

				if(num_indices_face>0)
				{
					int first=i;
					for(int j=i+2; j<num_verts_done; j++)
					{
						(*index_data)[num_indices_done]=first;
						num_indices_done++;
						(*index_data)[num_indices_done]=j-1;
						num_indices_done++;
						(*index_data)[num_indices_done]=j;
						num_indices_done++;
					}
					i=num_verts_done;
				}
			}
		}

		if(*num_vertices!=num_verts_done)
		{
			printf("[ERROR] number of processed vertices is differently than");
			printf(" expected\n");
		}

		if(*num_indices!=num_indices_done)
		{
			printf("[ERROR] number of processed indices is differently than");
			printf(" expected\n");
		}
	}


	//cleanup
	free(pos_array);
	free(tex_array);
	free(normal_array);
	fclose(file);

	return true;
}