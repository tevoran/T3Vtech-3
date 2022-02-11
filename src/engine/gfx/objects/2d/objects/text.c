#include <tt.h>

extern GLuint tt_gfx_2d_sprite_vao;
extern GLuint tt_gfx_2d_sprite_vbo;
extern GLuint tt_gfx_2d_sprite_ibo;

void tt_2d_object_make_text(
	tt_2d_object *object,
	const tt_font *font,
	const char *text)
{
	object->vao=tt_gfx_2d_sprite_vao;
	object->vbo=tt_gfx_2d_sprite_vbo;
	object->ibo=tt_gfx_2d_sprite_ibo;
	object->num_indices=6; //has 4 vertices and 6 total indices

	SDL_Color color={255, 255, 0, 255};
	SDL_Surface *text_surface=TTF_RenderUTF8_Solid(font->font, text, color);
	SDL_Surface *text_surfaceRGBA=SDL_CreateRGBSurfaceWithFormat(
		0,
		text_surface->w,
		text_surface->h,
		24,
		SDL_PIXELFORMAT_RGBA8888);

	tt_2d_texture *tmp_texture=tt_2d_texture_new_from_RGBA(
		text_surfaceRGBA->pixels, 
		text_surfaceRGBA->w,
		text_surfaceRGBA->h,
		false);
	tt_2d_object_use_texture(object, tmp_texture);

	SDL_FreeSurface(text_surface);
	SDL_FreeSurface(text_surfaceRGBA);
}