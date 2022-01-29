#include <tt.h>

extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//this is the beginning of the 2D object rendering list
extern tt_node *tt_2d_list_entry_node;
extern tt_node *tt_2d_list_last_entry;

void tt_gfx_2d_preparation()
{
	glUseProgram(tt_std_2d_shader);
	glDisable(GL_DEPTH_TEST);
}

void tt_gfx_2d_render()
{
	tt_2d_object *current_2d_object=NULL;
	if(tt_2d_list_entry_node)
	{
		current_2d_object=tt_2d_list_entry_node->data; //get the object
		tt_node *current_node=tt_2d_list_entry_node;

		int i=0;
		while(true) //actual 2d render loop
		{
				i++;
				//get uniforms
				GLint translation=glGetUniformLocation(tt_std_2d_shader, "translation");
				GLint scale=glGetUniformLocation(tt_std_2d_shader, "scale");

				//set uniforms
				glUniform2f(translation, current_2d_object->translation.x, current_2d_object->translation.y);
				glUniform2f(scale, current_2d_object->scale.x, current_2d_object->scale.y);

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
				glBindTexture(GL_TEXTURE_2D, current_2d_object->texture);

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
				current_2d_object=current_node->data;		
		}
	}
	tt_2d_object_clear_render_list();
}