#include <tt.h>

extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects

void tt_gfx_3d_preparation()
{
	glUseProgram(tt_std_3d_shader);
	glEnable(GL_DEPTH_TEST);

}