#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, true);

	tt_3d_object *quad=tt_3d_object_new();
	tt_3d_object_make_quad(quad);
	tt_vec3 pos={0,0,-7};
	tt_vec3 scale={2.8,1.0,1.0};
	tt_3d_object_set_position(quad, &pos);
	tt_3d_object_scale(quad, &scale);
	tt_3d_object_light_affected(quad, false);

	tt_font *font=tt_font_open("assets/fonts/OpenSans-Light.ttf", 50);
	tt_color_rgba_u8 color={255,255,255,255};

	tt_3d_texture *text=tt_3d_texture_make_text(font, "3D T3Vtech-3 test text", color);
	tt_3d_object_use_texture(quad, text);

	tt_vec3 rot_axis={0,1,0};

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		tt_3d_object_rotate(quad, &rot_axis, 0.01);
		tt_new_frame();
	}

	return 0;
}