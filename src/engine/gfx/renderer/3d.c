#include <tt.h>

extern uint32_t tt_res_x; //game resolution
extern uint32_t tt_res_y; //game resolution
extern float tt_near_plane; //near clipping plane
extern float tt_far_plane; //far clipping plane
extern float tt_fov; //field of view in radians
extern tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix
extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern bool tt_gfx_gouraud_shading_active; //toggle if gouraud shading is active
extern tt_vec3 tt_gfx_light_direction; //the current direction of the light
extern tt_vec3 tt_gfx_light_direction_color; //the current color of the directional light
extern float tt_gfx_light_direction_strength; //directional light strength


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

	//lighting
	GLint gouraud_shading_toggle=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_toggle");
	glUniform1i(gouraud_shading_toggle, tt_gfx_gouraud_shading_active);

	GLint light_direction=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_dir");
	glUniform3f(light_direction,
		tt_gfx_light_direction.x,
		tt_gfx_light_direction.y,
		tt_gfx_light_direction.z);

	GLint light_direction_color=glGetUniformLocation(tt_std_3d_shader, "gouraud_shading_color");
	glUniform3f(light_direction_color,
		tt_gfx_light_direction_color.x,
		tt_gfx_light_direction_color.y,
		tt_gfx_light_direction_color.z);

	GLint light_direction_strength=glGetUniformLocation(
		tt_std_3d_shader,
		"gouraud_shading_light_strength");
	glUniform1f(light_direction_strength, tt_gfx_light_direction_strength);
}
