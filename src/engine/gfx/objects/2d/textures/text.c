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

	SDL_Surface *text_surface=TTF_RenderUTF8_Solid(font->font, text, color_tmp);
	if(!text_surface)
	{
		printf("[ERROR] error while rendering the text into a surface\n");
		printf("SDL2_ttf error message:\n%s\n", TTF_GetError());
	}

	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	if(!format)
	{
		printf("ERROR: color format couldn't be allocated RGBA\n");
		printf("SDL2 error message:\n%s\n", SDL_GetError());	
	}

	SDL_Surface *text_surface_rgba=
		SDL_ConvertSurface(text_surface, format, 0);
	if(!text_surface_rgba)
	{
		printf("ERROR: text surface couldn't be converted into RGBA\n");
		printf("SDL2 error message:\n%s\n", SDL_GetError());		
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