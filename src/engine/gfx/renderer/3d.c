#include <tt.h>

#define DIR_LIGHT_BINDING 0

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
extern GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data

//ambient lighting
extern float tt_gfx_amb_light_strength; //the ambient light strength
extern tt_vec3 tt_gfx_amb_light_color; //the ambient light color

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

void tt_gfx_3d_preparation()
{
	glUseProgram(tt_std_3d_shader);
	glEnable(GL_DEPTH_TEST);

	//setting the perspective projection matrix
	GLint projection_mat=glGetUniformLocation(tt_std_3d_shader, "projection");
	const GLfloat *projection_mat_ptr=(const GLfloat*) tt_perspective_projection_mat.array;
	glUniformMatrix4fv(projection_mat, 1, GL_FALSE, projection_mat_ptr);

	//camera
	GLint cam_translation=glGetUniformLocation(tt_std_3d_shader, "cam_translation");
	const GLfloat *cam_translation_ptr=(const GLfloat*)tt_camera_position.array;
	glUniformMatrix4fv(cam_translation, 1, GL_FALSE, cam_translation_ptr);

	GLint cam_rotation=glGetUniformLocation(tt_std_3d_shader, "cam_rotation");
	const GLfloat *cam_rotation_ptr=(const GLfloat*)tt_camera_rotation.array;
	glUniformMatrix4fv(cam_rotation, 1, GL_FALSE, cam_rotation_ptr);

	//lighting
	GLint gouraud_shading_toggle=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_toggle");
	glUniform1i(gouraud_shading_toggle, tt_gfx_gouraud_shading_active);

	//directional light uniform buffer object
	GLuint dir_light=glGetUniformBlockIndex(tt_std_3d_shader, "dir_light");
	glUniformBlockBinding(tt_std_3d_shader, dir_light, DIR_LIGHT_BINDING);
	glBindBufferBase(GL_UNIFORM_BUFFER, DIR_LIGHT_BINDING, tt_gfx_ubo_dir_light);

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
