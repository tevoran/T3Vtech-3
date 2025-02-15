#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, NULL);

	tt_2d_object *sprite = tt_2d_object_new();
	tt_2d_object_make_sprite(sprite);
	tt_vec2 pos = {0.1,0.5};
	tt_2d_object_set_position(sprite, &pos);
	tt_vec2 scale = {0.8,0.1};
	tt_2d_object_scale(sprite, &scale);

	tt_font *font = tt_font_open("assets/fonts/OpenSans-Light.ttf", 50);
	tt_color_rgba_u8 color = {255,255,255,255};
	tt_2d_texture *tex = NULL;
	tex = tt_2d_texture_make_text(font, "2D Transparency Test", color);
	tt_2d_object_use_texture(sprite, tex);


	float time = 0.0f;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		time += tt_time_current_frame_s();
		tt_2d_object_set_transparency(sprite, sin(time));
		tt_2d_object_render(sprite);
		tt_new_frame();
	}

	return 0;
}