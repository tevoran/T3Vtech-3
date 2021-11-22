#include <tt.h>

extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

void tt_gfx_2d_preparation()
{
	glUseProgram(tt_std_2d_shader);
	glDisable(GL_DEPTH_TEST);
}