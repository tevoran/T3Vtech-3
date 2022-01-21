#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 720, false, 16, false);


	tt_3d_object *cube=tt_3d_object_new();
	tt_3d_object_make_cube(cube);
	tt_vec3 cube_pos={0,0,4};
	tt_3d_object_set_position(cube, &cube_pos);

	tt_3d_texture *crate=tt_3d_texture_new("assets/smiley.png", false);
	tt_3d_object_use_texture(cube, crate);



	tt_vec3 dir_light_dir={-1,0,0};
	tt_vec3 color_dir_light={1.0,0.0,0.0};
	tt_dir_light l1=tt_directional_light_new();
	tt_directional_light_set_color(l1, &color_dir_light);
	tt_directional_light_set_strength(l1, 1);
	tt_directional_light_set_direction(l1, &dir_light_dir);

	tt_dir_light l2=tt_directional_light_new();
	tt_vec3 dir_light_dir_2={1,0,0};
	tt_vec3 color_dir_light_2={0.0,0.0,1.0};
	tt_directional_light_set_color(l2, &color_dir_light_2);
	tt_directional_light_set_strength(l2, 1);
	tt_directional_light_set_direction(l2, &dir_light_dir_2);

	tt_dir_light l3=tt_directional_light_new();
	tt_vec3 dir_light_dir_3={0,-1,0};
	tt_vec3 color_dir_light_3={0.0,1.0,0.0};
	tt_directional_light_set_color(l3, &color_dir_light_3);
	tt_directional_light_set_strength(l3, 1);
	tt_directional_light_set_direction(l3, &dir_light_dir_3);

	int i=0;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
	i++;

	tt_vec3 rot_axis={1,1,0};
	if(tt_input_mouse_button_down(TT_MOUSE_LEFT))
	{
		tt_3d_object_rotate(cube, &rot_axis, 0.01);
	}

		tt_directional_light_delete(l2);
		l2=tt_directional_light_new();
		tt_directional_light_set_color(l2, &color_dir_light_2);
		tt_directional_light_set_strength(l2, 1);
		tt_directional_light_set_direction(l2, &dir_light_dir_2);

		tt_new_frame();
	}

	return 0;
}