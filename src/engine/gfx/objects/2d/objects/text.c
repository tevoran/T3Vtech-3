#include <tt.h>


void tt_2d_object_make_text(
	tt_2d_object *object,
	const tt_font *font,
	const char *text)
{
	SDL_Color color={255, 255, 0, 255};
	SDL_Surface *text_surface=TTF_RenderUTF8_Solid(font->font, text, color);
	
	SDL_FreeSurface(text_surface);
}