#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 720, false, 16, false);


	tt_3d_object *cube=tt_3d_object_new();
	tt_3d_object_make_cube(cube);
	tt_vec3 cube_pos={0,0,2};
	tt_3d_object_set_position(cube, &cube_pos);

	tt_3d_texture *crate=tt_3d_texture_new("assets/smiley.png", false);
	tt_3d_object_use_texture(cube, crate);



	tt_vec3 pos_point_light={0,0,20};
	tt_vec3 color_point_light={0.99,0.95,0.93};
	tt_point_light_new();
	pos_point_light.y=0;
	pos_point_light.z=15;
	tt_point_light_new();
	tt_point_light_set_color(1, &color_point_light);
	tt_point_light_set_color(2, &color_point_light);

	//glDisable(GL_MULTISAMPLE); 

	int i=0;
	while(!tt_input_keyboard_key_pressed(TT_KEY_ESC))
	{

	if(tt_input_controller_button_press(TT_CTL_X))
	{
		printf("X\n");
	}

	i++;
	static long time=0;
	static long time_new=0;

	tt_vec3 rot_axis={1,1,0};
	tt_3d_object_rotate(cube, &rot_axis, 0.02);

		tt_point_light_set_strength(1, 5);
			pos_point_light.x=40*sin((float)i/100);
			pos_point_light.y=40*cos((float)i/100);
		tt_point_light_set_position(2, &pos_point_light);
		tt_point_light_set_strength(2, 15);

		tt_ambient_light_set_strength(0.0);
		tt_vec3 amb_color={
			sin((float)i/30),
			sin((float)i/135),
			sin((float)i/354)};
		tt_ambient_light_set_color(&amb_color);

		tt_new_frame();
		//SDL_Delay(15);

		//tt_vec3 light_direction={sin((float)i/60),0.0,cos((float)i/60)};
		//tt_gfx_set_light_direction(&light_direction);
		if(i==10000)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={-1,0,0};
			tt_vec3 light_color={0, 1, 0};
			tt_directional_light_set_direction(1, &light_direction);
			tt_directional_light_set_strength(1, 1);
			tt_directional_light_set_color(1, &light_color);
		}

		if(i==13000)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={0,0,1};
			tt_vec3 light_color={0.9, 0.86, 0.5};
			tt_directional_light_set_direction(2, &light_direction);
			tt_directional_light_set_strength(2, 1);
			tt_directional_light_set_color(2, &light_color);
		}
	}

	return 0;
}