#include <tt.h>

extern GLuint tt_gfx_2d_default_tex; //default texture

GLubyte default_tex_2d[]=
{
	255, 0, 255
};

void tt_gfx_2d_default_tex_init()
{
	glGenTextures(1, &tt_gfx_2d_default_tex);
	glBindTexture(GL_TEXTURE_2D, tt_gfx_2d_default_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, default_tex_2d);
}
