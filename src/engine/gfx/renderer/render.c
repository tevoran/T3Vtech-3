#include <tt.h>

extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;


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
			glBindVertexArray(current_object->vao);
			glBindBuffer(GL_ARRAY_BUFFER, current_object->vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, current_object->ibo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, (void*)0);
			glEnableVertexAttribArray(0);

			glDrawElements(
				GL_TRIANGLES,
				current_object->num_verts,
				GL_UNSIGNED_INT,
				NULL);


			//get to the next object to render
			current_node=tt_list_next_node(current_node);
			if(!current_node)
			{
				break;
			}
			current_object=current_node->data;
		}
	}

	//render 2D stuff
	tt_gfx_2d_preparation();
}