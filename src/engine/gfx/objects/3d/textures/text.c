#include <tt.h>


tt_3d_texture* tt_3d_texture_make_text(
	const tt_font *font,
	const char *text,
	const tt_color_rgba_u8 color)
{
	tt_3d_texture *new_texture=malloc(sizeof(tt_3d_texture));

	tt_2d_texture *new_2d_texture=tt_2d_texture_make_text(font, text, color);
	new_texture->texture=new_2d_texture->texture;

	return new_texture;
}