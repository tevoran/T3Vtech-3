#include <tt.h>


tt_2d_texture* tt_2d_texture_make_text(
	const tt_font *font,
	const char *text,
	const tt_color_rgba_u8 color)
{
	SDL_Color color_tmp;
		color_tmp.r=color.r;
		color_tmp.g=color.g;
		color_tmp.b=color.b;
		color_tmp.a=color.a;

	if(!font)
	{
		tt_log(TT_ERROR, "font missing");
		return NULL;
	}

	SDL_Surface *text_surface = TTF_RenderUTF8_Blended(font->font, text, color_tmp);
	if(!text_surface)
	{
		tt_log(TT_ERROR, "error while rendering the text into a surface");
		tt_log(TT_ERROR, "SDL2_ttf error message:\n%s", TTF_GetError());
	}

	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	if(!format)
	{
		tt_log(TT_ERROR, "color format couldn't be allocated RGBA");
		tt_log(TT_ERROR, "SDL2 error message:\n%s", SDL_GetError());	
	}

	SDL_Surface *text_surface_rgba=
		SDL_ConvertSurface(text_surface, format, 0);
	if(!text_surface_rgba)
	{
		tt_log(TT_ERROR, "text surface couldn't be converted into RGBA");
		tt_log(TT_ERROR, "SDL2 error message:\n%s", SDL_GetError());		
	}

	tt_2d_texture *tmp_texture=tt_2d_texture_new_from_RGBA(
		text_surface_rgba->pixels, 
		text_surface_rgba->w,
		text_surface_rgba->h,
		false);

	SDL_FreeSurface(text_surface);
	SDL_FreeSurface(text_surface_rgba);
	SDL_FreeFormat(format);
	return tmp_texture;
}