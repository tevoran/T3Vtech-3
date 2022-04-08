#include <tt.h>

#define DIR_LIGHT_BINDING 0
#define POINT_LIGHT_BINDING 1

//game settings
extern uint32_t tt_res_x; //game resolution
extern uint32_t tt_res_y; //game resolution

//projection data
extern float tt_near_plane; //near clipping plane
extern float tt_far_plane; //far clipping plane
extern float tt_fov; //field of view in radians
extern tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix

//camera
extern tt_mat4 tt_camera_position; //current camera position
extern tt_mat4 tt_camera_rotation; //current camera rotation

//shader stuff
extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern bool tt_gfx_gouraud_shading_active; //toggle if gouraud shading is active
extern bool tt_gfx_phong_shading_active; //toggle if phong shading is active
extern bool tt_gfx_tone_mapping_toggle; //toggle if tone mapping is enabled
extern GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data
extern GLuint tt_gfx_ubo_point_light; //uniform buffer object for point light data

//ambient lighting
extern float tt_gfx_amb_light_strength; //the ambient light strength
extern tt_vec3 tt_gfx_amb_light_color; //the ambient light color

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

//setting the field of view
void tt_set_fov(float radians)
{
	tt_fov=radians;
	tt_math_mat4_make_projection_matrix(
		&tt_perspective_projection_mat,
		tt_res_x,
		tt_res_y,
		tt_fov,
		tt_near_plane,
		tt_far_plane);	
}

void tt_set_far_plane(float distance)
{
	tt_far_plane = distance;
	tt_math_mat4_make_projection_matrix(
		&tt_perspective_projection_mat,
		tt_res_x,
		tt_res_y,
		tt_fov,
		tt_near_plane,
		tt_far_plane);
}

void tt_gfx_3d_preparation()
{
	glUseProgram(tt_std_3d_shader);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//global camera and projection matrix
	tt_mat4 mat4_cam_and_projection=tt_math_mat4_mul(&tt_camera_rotation, &tt_camera_position);
	mat4_cam_and_projection=tt_math_mat4_mul(&tt_perspective_projection_mat, &mat4_cam_and_projection);
	GLint cam_and_projection_mat=glGetUniformLocation(tt_std_3d_shader, "cam_and_projection");
	const GLfloat *cam_and_projection_mat_ptr=(const GLfloat*) &mat4_cam_and_projection.array;
	glUniformMatrix4fv(cam_and_projection_mat, 1, GL_TRUE, cam_and_projection_mat_ptr);

	//lighting
	GLint gouraud_shading_toggle=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_toggle");
	glUniform1i(gouraud_shading_toggle, tt_gfx_gouraud_shading_active);

	GLint phong_shading_toggle = glGetUniformLocation(tt_std_3d_shader, "phong_shading_toggle");
	glUniform1i(phong_shading_toggle, tt_gfx_phong_shading_active);

	//global settings
	GLint tone_mapping_toggle = glGetUniformLocation(tt_std_3d_shader, "tone_mapping_toggle");
	glUniform1i(tone_mapping_toggle, tt_gfx_tone_mapping_toggle);

	//directional light uniform buffer object
	GLuint dir_light=glGetUniformBlockIndex(tt_std_3d_shader, "dir_light");
	glUniformBlockBinding(tt_std_3d_shader, dir_light, DIR_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, DIR_LIGHT_BINDING, tt_gfx_ubo_dir_light);

	//point light uniform buffer object
	GLuint point_light=glGetUniformBlockIndex(tt_std_3d_shader, "point_light");
	glUniformBlockBinding(tt_std_3d_shader, point_light, POINT_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, POINT_LIGHT_BINDING, tt_gfx_ubo_point_light);

	//ambient lighting
	GLint amb_light_strength=glGetUniformLocation(tt_std_3d_shader, "amb_light_strength"); 
	glUniform1f(amb_light_strength, tt_gfx_amb_light_strength);

	GLint amb_light_color=glGetUniformLocation(tt_std_3d_shader, "amb_light_color");
	glUniform3f(
		amb_light_color,
		tt_gfx_amb_light_color.x,
		tt_gfx_amb_light_color.y,
		tt_gfx_amb_light_color.z);
}

void tt_gfx_3d_render()
{
	tt_3d_object *current_object=NULL;
	if(tt_3d_list_entry_node)
	{
		current_object=tt_3d_list_entry_node->data;
		tt_node *current_node=tt_3d_list_entry_node;

		while(true)
		{
			if(	!current_object->invisibility_toggle) //if invisible there is no need to render 
			{
				//prepare uniforms
				GLint transform=glGetUniformLocation(tt_std_3d_shader, "transform");
				GLint rotation=glGetUniformLocation(tt_std_3d_shader, "rotation");
				GLint affected_by_light=glGetUniformLocation(tt_std_3d_shader, "object_light_affected");

				//calculate object transformation matrix
				tt_mat4 mat4_transform=tt_math_mat4_mul(&current_object->translation, &current_object->rotation);
				mat4_transform=tt_math_mat4_mul(&mat4_transform, &current_object->scale);

				const GLfloat *mat4_uniform=NULL;

				//set uniforms
				mat4_uniform=(const GLfloat*)current_object->rotation.array;
				glUniformMatrix4fv(rotation, 1, GL_TRUE, mat4_uniform);

				mat4_uniform=(const GLfloat*)&mat4_transform;
				glUniformMatrix4fv(transform, 1, GL_TRUE, mat4_uniform);

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
}
