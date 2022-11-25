#include <tt.h>

#define DIR_LIGHT_BINDING 0
#define POINT_LIGHT_BINDING 1
#define AO_LIGHT_BINDING 2

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
extern float tt_gfx_exposure; //full scene exposure
extern float tt_gfx_saturation; //full scene saturation
extern float tt_gfx_contrast; //full scene contrast
extern GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data
extern GLuint tt_gfx_ubo_point_light; //uniform buffer object for point light data
extern GLuint tt_gfx_ubo_ao_light; //uniform buffer object for ao light data

//ambient lighting
extern float tt_gfx_amb_light_strength; //the ambient light strength
extern tt_vec3 tt_gfx_amb_light_color; //the ambient light color

//this is the beginning of the 3D object rendering list
extern T_node *tt_3d_list_entry_node;

//frustum culling
extern bool tt_frustum_culling_trigger; //whether frustum culling is active or not

tt_vec3 tt_gfx_frustum_culling_frustum_pos;
float tt_gfx_frustum_culling_frustum_distance;


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
	glEnable(GL_CULL_FACE); //GL_BACK is the default


	//global camera and projection matrix
	tt_mat4 mat4_cam_and_projection=tt_math_mat4_mul(&tt_camera_rotation, &tt_camera_position);
	mat4_cam_and_projection=tt_math_mat4_mul(&tt_perspective_projection_mat, &mat4_cam_and_projection);
	GLint cam_and_projection_mat=glGetUniformLocation(tt_std_3d_shader, "cam_and_projection");
	const GLfloat *cam_and_projection_mat_ptr=(const GLfloat*) &mat4_cam_and_projection.array;
	glUniformMatrix4fv(cam_and_projection_mat, 1, GL_TRUE, cam_and_projection_mat_ptr);

	//lighting
	tt_gfx_directional_light_update_ubo();
	tt_gfx_point_light_update_ubo();
	tt_gfx_ao_light_update_ubo();

	GLint gouraud_shading_toggle=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_toggle");
	glUniform1i(gouraud_shading_toggle, tt_gfx_gouraud_shading_active);

	GLint phong_shading_toggle = glGetUniformLocation(tt_std_3d_shader, "phong_shading_toggle");
	glUniform1i(phong_shading_toggle, tt_gfx_phong_shading_active);

	//global settings
	GLint tone_mapping_toggle = glGetUniformLocation(tt_std_3d_shader, "tone_mapping_toggle");
	glUniform1i(tone_mapping_toggle, tt_gfx_tone_mapping_toggle);

	GLint exposure = glGetUniformLocation(tt_std_3d_shader, "exposure");
	glUniform1f(exposure, tt_gfx_exposure);

	GLint saturation = glGetUniformLocation(tt_std_3d_shader, "saturation");
	glUniform1f(saturation, tt_gfx_saturation);

	GLint contrast = glGetUniformLocation(tt_std_3d_shader, "contrast");
	glUniform1f(contrast, tt_gfx_contrast);

	//directional light uniform buffer object
	GLuint dir_light=glGetUniformBlockIndex(tt_std_3d_shader, "dir_light");
	glUniformBlockBinding(tt_std_3d_shader, dir_light, DIR_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, DIR_LIGHT_BINDING, tt_gfx_ubo_dir_light);

	//point light uniform buffer object
	GLuint point_light=glGetUniformBlockIndex(tt_std_3d_shader, "point_light");
	glUniformBlockBinding(tt_std_3d_shader, point_light, POINT_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, POINT_LIGHT_BINDING, tt_gfx_ubo_point_light);

	//ao light uniform buffer object
	GLuint ao_light = glGetUniformBlockIndex(tt_std_3d_shader, "ao_light");
	glUniformBlockBinding(tt_std_3d_shader, ao_light, AO_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, AO_LIGHT_BINDING, tt_gfx_ubo_ao_light);

	//ambient lighting
	GLint amb_light_strength=glGetUniformLocation(tt_std_3d_shader, "amb_light_strength"); 
	glUniform1f(amb_light_strength, tt_gfx_amb_light_strength);

	GLint amb_light_color=glGetUniformLocation(tt_std_3d_shader, "amb_light_color");
	glUniform3f(
		amb_light_color,
		tt_gfx_amb_light_color.x,
		tt_gfx_amb_light_color.y,
		tt_gfx_amb_light_color.z);

	//frustum culling
	tt_gfx_frustum_culling_frustum_pos=tt_camera_get_position();
	tt_vec3 view_dir=tt_camera_view_direction();
	view_dir=tt_math_vec3_mul_float(&view_dir, 0.5f * tt_far_plane);
	tt_gfx_frustum_culling_frustum_pos=tt_math_vec3_add(&view_dir, &tt_gfx_frustum_culling_frustum_pos);

	float alpha=0.5f * tt_fov;
	float beta=tt_PI - 0.5f * tt_PI - alpha;
	tt_gfx_frustum_culling_frustum_distance=
		tt_far_plane
		* tt_far_plane
		* (sin(alpha) * sin(alpha)
			/ (sin(beta) * sin(beta))
			* 0.25f);
}

void tt_gfx_3d_render()
{
	tt_3d_object *current_object=NULL;
	if(tt_3d_list_entry_node)
	{
		current_object=tt_3d_list_entry_node->data;
		T_node *current_node=tt_3d_list_entry_node;

		while(true)
		{
			if(!current_object->invisibility_toggle) //if invisible there is no need to render 
			{
				//frustum culling
				float a, b, c, distance;
				a=tt_gfx_frustum_culling_frustum_pos.x - current_object->translation.array[0][3];
				b=tt_gfx_frustum_culling_frustum_pos.y - current_object->translation.array[1][3];
				c=tt_gfx_frustum_culling_frustum_pos.z - current_object->translation.array[2][3];
				a=a*a;
				b=b*b;
				c=c*c;
				distance=a+b+c;
				distance=distance-current_object->bounding_sphere_radius;
				if(distance<tt_gfx_frustum_culling_frustum_distance || !tt_frustum_culling_trigger) //if inside rendering sphere then render
				{
					//deactivate back face culling if not desired for this object
					if(!current_object->backface_culling_toggle)
					{
						glDisable(GL_CULL_FACE);
					}

					//prepare uniforms
					GLint transform=glGetUniformLocation(tt_std_3d_shader, "transform");
					GLint rotation=glGetUniformLocation(tt_std_3d_shader, "rotation");
					GLint affected_by_light=glGetUniformLocation(tt_std_3d_shader, "object_light_affected");
					GLint point_light_count=glGetUniformLocation(tt_std_3d_shader, "object_point_light_count");
					GLint point_light_list=glGetUniformLocation(tt_std_3d_shader, "object_point_lights");
					GLint ao_light_count=glGetUniformLocation(tt_std_3d_shader, "object_ao_light_count");
					GLint ao_light_list=glGetUniformLocation(tt_std_3d_shader, "object_ao_lights");
					GLint object_color=glGetUniformLocation(tt_std_3d_shader, "object_color");
					GLint object_emission=glGetUniformLocation(tt_std_3d_shader, "object_emission");

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
					glUniform1i(point_light_count, current_object->point_light_count);
					glUniform1iv(point_light_list, current_object->point_light_count, (const GLint *)current_object->point_lights);
					glUniform1i(ao_light_count, current_object->ao_light_count);
					glUniform1iv(ao_light_list, current_object->ao_light_count, (const GLint *)current_object->ao_lights);
					glUniform3f(object_color, current_object->color.x, current_object->color.y, current_object->color.z);
					glUniform3f(object_emission, current_object->emission.x, current_object->emission.y, current_object->emission.z);

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

					if(!current_object->backface_culling_toggle)
					{
						glEnable(GL_CULL_FACE);
					}
				}
					
			}

			//get to the next object to render
			current_node=T_list_next_node(current_node);
			if(!current_node) //if no following object is left then exit
			{
				break;
			}
			current_object=current_node->data;
		}
	}	
}
