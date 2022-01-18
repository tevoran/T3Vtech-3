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



	tt_vec3 pos_point_light={0,0,0};
	tt_vec3 color_point_light={1.0,0.0,0.0};
	tt_point_light l1=tt_point_light_new();
	tt_point_light l2=tt_point_light_new();
	tt_point_light l3=tt_point_light_new();
	tt_point_light_set_color(l1, &color_point_light);
	color_point_light.x=0;
	color_point_light.y=1.0;
	tt_point_light_set_color(l2, &color_point_light);
	color_point_light.y=0;
	color_point_light.z=1.0;
	tt_point_light_set_color(l3, &color_point_light);

	tt_point_light_set_strength(l1, 40);
	tt_point_light_set_strength(l2, 40);
	tt_point_light_set_strength(l3, 40);

	int i=0;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
	i++;
	static long time=0;
	static long time_new=0;

	tt_vec3 rot_axis={1,1,0};
	if(tt_input_mouse_button_down(TT_MOUSE_LEFT))
	{
		tt_3d_object_rotate(cube, &rot_axis, 0.02);
	}

		tt_point_light_delete(l1);
		l1=tt_point_light_new();
		printf("%i %i %i\n", l1, l2, l3);
		color_point_light.x=1.0;
		color_point_light.y=0.0;
		color_point_light.z=0.0;
		tt_point_light_set_color(l1, &color_point_light);
			pos_point_light.y=0;
			pos_point_light.x=40*sin((float)i/100 + 0.0*tt_PI);
			pos_point_light.z=40*cos((float)i/100 + 0.0*tt_PI);
		tt_point_light_set_position(l1, &pos_point_light);
		tt_point_light_set_strength(l1, 40);
			pos_point_light.y=0;
			pos_point_light.x=40*sin((float)i/100 + 1.0*tt_PI);
			pos_point_light.z=40*cos((float)i/100 + 1.0*tt_PI);
		tt_point_light_set_position(l2, &pos_point_light);
			pos_point_light.y=0;
			pos_point_light.x=40*sin((float)i/100 + 1.5*tt_PI);
			pos_point_light.z=40*cos((float)i/100 + 1.5*tt_PI);
		tt_point_light_set_position(l3, &pos_point_light);

		tt_ambient_light_set_strength(0.0);
		tt_vec3 amb_color={
			sin((float)i/30),
			sin((float)i/135),
			sin((float)i/354)};
		tt_ambient_light_set_color(&amb_color);

		tt_new_frame();
	}

	return 0;
}