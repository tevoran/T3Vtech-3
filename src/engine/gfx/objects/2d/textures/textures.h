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
tt_2d_texture* tt_2d_texture_new_from_RGBA(
	void *image_data, 
	const int res_x,
	const int res_y,
	const bool bilinear_filtering);
void tt_2d_texture_delete(tt_2d_texture **texture);
int tt_2d_texture_get_width(tt_2d_texture *texture);
int tt_2d_texture_get_height(tt_2d_texture *texture);
float tt_2d_texture_get_aspect_ratio(tt_2d_texture *texture);


//text textures
tt_2d_texture* tt_2d_texture_make_text(
	const tt_font *font,
	const char *text,
	const tt_color_rgba_u8 color);

#endif