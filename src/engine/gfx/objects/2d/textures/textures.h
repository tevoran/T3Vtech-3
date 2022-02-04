#ifndef TT_GFX_TEXTURE_2D_H
#define TT_GFX_TEXTURE_2D_H

#include <tt.h>

struct tt_2d_texture
{
	GLuint texture;
} typedef tt_2d_texture;

//internal functions
void tt_gfx_2d_default_tex_init();

//functions
tt_2d_texture* tt_2d_texture_new(const char *path, const bool bilinear_filtering);

#endif