#include <tt.h>

extern tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix
extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects

void tt_gfx_3d_preparation()
{
	glUseProgram(tt_std_3d_shader);
	glEnable(GL_DEPTH_TEST);

	//setting the perspective projection matrix
	GLint projection_mat=glGetUniformLocation(tt_std_3d_shader, "projection");
	const GLfloat *projection_mat_ptr=(const GLfloat*) tt_perspective_projection_mat.array;
	glUniformMatrix4fv(projection_mat, 1, GL_FALSE, projection_mat_ptr);
}