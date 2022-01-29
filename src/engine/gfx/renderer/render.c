#include <tt.h>

extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

//this is the beginning of the 2D object rendering list
extern tt_node *tt_2d_list_entry_node;
extern tt_node *tt_2d_list_last_entry;

void tt_gfx_render()
{
	//render 3D stuff
	tt_gfx_3d_preparation();
	
	tt_3d_object *current_object=NULL;
	if(tt_3d_list_entry_node)
	{
		current_object=tt_3d_list_entry_node->data;
		tt_node *current_node=tt_3d_list_entry_node;

		while(true)
		{
			if(!current_object->invisibility_toggle) //if invisible there is no need to render
			{
				//prepare uniforms
				GLint translation=glGetUniformLocation(tt_std_3d_shader, "translation");
				GLint scale=glGetUniformLocation(tt_std_3d_shader, "scale");
				GLint rotation=glGetUniformLocation(tt_std_3d_shader, "rotation");
				GLint affected_by_light=glGetUniformLocation(tt_std_3d_shader, "object_light_affected");

				//set uniforms
				const GLfloat *mat4_uniform=(const GLfloat*)current_object->translation.array;
				glUniformMatrix4fv(translation, 1, GL_FALSE, mat4_uniform);

				mat4_uniform=(const GLfloat*)current_object->scale.array;
				glUniformMatrix4fv(scale, 1, GL_FALSE, mat4_uniform);
				
				mat4_uniform=(const GLfloat*)current_object->rotation.array;
				glUniformMatrix4fv(rotation, 1, GL_FALSE, mat4_uniform);

				glUniform1i(affected_by_light, current_object->lighting_affected);

				//bind buffers
				//glBindVertexArray(current_object->vao);
				glBindBuffer(GL_ARRAY_BUFFER, current_object->vbo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, current_object->ibo);

				//describe vertex data
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));
				glEnableVertexAttribArray(2);

				//use textures
				glBindTexture(GL_TEXTURE_2D, current_object->texture);
				
				glDrawElements(
					GL_TRIANGLES,
					current_object->num_indices,
					GL_UNSIGNED_INT,
					NULL);
					
			}


			//get to the next object to render
			current_node=tt_list_next_node(current_node);
			if(!current_node) //if no following object is left then exit
			{
				break;
			}
			current_object=current_node->data;
		}
	}

	//render 2D stuff
	tt_gfx_2d_preparation();

	tt_2d_object *current_2d_object=NULL;
	if(tt_2d_list_entry_node)
	{
		current_2d_object=tt_2d_list_entry_node->data; //get the object
		tt_node *current_node=tt_2d_list_entry_node;

		while(true) //actual 2d render loop
		{
				//get uniforms
				GLint translation=glGetUniformLocation(tt_std_2d_shader, "translation");		

				//set uniforms
				glUniform2f(translation, current_2d_object->translation.x, current_2d_object->translation.y);

				//bind buffers
				//glBindVertexArray(current_object->vao);
				glBindBuffer(GL_ARRAY_BUFFER, current_2d_object->vbo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, current_2d_object->ibo);

				//describe vertex data
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
				glEnableVertexAttribArray(1);
				
				//use textures
				//glBindTexture(GL_TEXTURE_2D, current_2d_object->texture);

				glDrawElements(
					GL_TRIANGLES,
					current_2d_object->num_indices,
					GL_UNSIGNED_INT,
					NULL);

				//go to next element in the 2D render element
				current_node=tt_list_next_node(current_node);
				if(!current_node) //if no following object is left then exit
				{
					break;
				}
				current_object=current_node->data;		
		}

	}

	tt_2d_object_clear_render_list();
}
