#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, true);

	tt_2d_object *sprite = tt_2d_object_new();
	tt_2d_object_make_sprite(sprite);
	tt_vec2 pos = {0.1,0.5};
	tt_2d_object_set_position(sprite, &pos);
	tt_vec2 scale = {0.8,0.1};
	tt_2d_object_scale(sprite, &scale);

	tt_font *font = tt_font_open("assets/fonts/OpenSans-Light.ttf", 50);
	tt_color_rgba_u8 color = {255,255,255,255};

	tt_2d_texture *tex = NULL;

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		if(tt_input_mouse_button_down(TT_MOUSE_LEFT))
		{
			tex = tt_2d_texture_make_text(font, "left mouse button is continuosly pressed down", color);
			tt_2d_object_use_texture(sprite, tex);
		}
		if(tt_input_mouse_button_press(TT_MOUSE_RIGHT))
		{
			tex = tt_2d_texture_make_text(font, "right mouse button is pressed once for a frame", color);
			tt_2d_object_use_texture(sprite, tex);
		}
		if(tt_input_keyboard_key_down(TT_KEY_A))
		{
			tex = tt_2d_texture_make_text(font, "A key is continuosly pressed down", color);
			tt_2d_object_use_texture(sprite, tex);
		}
		if(tt_input_keyboard_key_press(TT_KEY_D))
		{
			tex = tt_2d_texture_make_text(font, "D key is pressed once for a frame", color);
			tt_2d_object_use_texture(sprite, tex);
		}
		if(tex)
		{
			tt_2d_object_render(sprite);
		}
		tt_new_frame();
		SDL_Delay(1000);
		if(tex)
		{
			tt_2d_texture_delete(&tex);
		}
	}

	return 0;
}