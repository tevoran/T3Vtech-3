#ifndef TT_GFX_TEXTURE_H
#define TT_GFX_TEXTURE_H

struct tt_3d_texture
{
	GLuint texture;
} typedef tt_3d_texture;

//initialization
void tt_gfx_3d_default_tex_init();

tt_3d_texture* tt_3d_texture_make_text(
	const tt_font *font,
	const char *text,
	const tt_color_rgba_u8 color);

//3D texture object
tt_3d_texture* tt_3d_texture_new(const char *path, const bool bilinear_filtering);
void tt_3d_texture_delete(tt_3d_texture **texture);
#endif