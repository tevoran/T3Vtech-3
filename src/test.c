#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1920, 1080, true);

	float fov=0.5*tt_PI;
	tt_vec3 pos={-10.0,0.0,20.0};
	tt_vec3 scale={1,1,1};
	tt_vec3 orientation={0.5,0.5,0.0};
	tt_3d_object *ship=tt_3d_object_new();
	tt_3d_object *ship_r=tt_3d_object_new();

	tt_3d_object_set_position(ship, &pos);
	pos.x=10;
	tt_3d_object_set_position(ship_r, &pos);

	tt_vec3 rot_axis={1,0,0};

	tt_3d_custom_model *ship_model=tt_3d_custom_model_load_file("assets/models/ship/ship.obj");
	tt_3d_texture *ship_tex=tt_3d_texture_new("assets/models/ship/ship_low.png", false);
	tt_3d_object_use_texture(ship, ship_tex);
	tt_3d_object_use_custom_model(ship, ship_model);
	tt_3d_object_use_texture(ship_r, ship_tex);
	tt_3d_object_use_custom_model(ship_r, ship_model);


	tt_3d_object_rotate(ship, &rot_axis, -0.3*tt_PI);
	tt_3d_object_rotate(ship_r, &rot_axis, -0.3*tt_PI);

	tt_vec3 cam_pos={0,0,0};
	tt_vec3 cam_rot_axis={1,0,0};
	//tt_camera_rotate(&cam_rot_axis, -tt_PI/8);

	tt_vec3 pos_point_light={0,0,0};
	tt_vec3 color_point_light={1,1,0};
	tt_point_light_new(&pos_point_light, &color_point_light);
/*	pos_point_light.z=0;
	pos_point_light.x=5;
	color_point_light.x=0.7;
	color_point_light.y=0.8;	
	color_point_light.z=0.2;
	tt_point_light_new(&pos_point_light, &color_point_light);
*/
	for(int i=0; i<1500; i++)
	{
		pos_point_light.z+=0.02;
		tt_point_light_set_position(1, &pos_point_light);
		//cam_pos.y+=0.01;
		//tt_camera_set_position(&cam_pos);
		//tt_camera_rotate(&cam_rot_axis, 0.004*sin((float)i/100));

		//tt_point_light_set_strength(1, 1.5+1.5*sin((float)i/100));
		tt_ambient_light_set_strength(0);
		tt_vec3 amb_color={
			sin((float)i/30),
			sin((float)i/135),
			sin((float)i/354)};
		tt_ambient_light_set_color(&amb_color);

		tt_new_frame();
		//SDL_Delay(15);

		//tt_vec3 light_direction={sin((float)i/60),0.0,cos((float)i/60)};
		//tt_gfx_set_light_direction(&light_direction);
		if(i==1000000)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={-1,0,0};
			tt_vec3 light_color={0, 1, 0};
			tt_directional_light_set_direction(1, &light_direction);
			tt_directional_light_set_strength(1, 0.1);
			tt_directional_light_set_color(1, &light_color);
		}
	}

	tt_3d_texture_delete(&ship_tex);
	tt_3d_custom_model_delete(&ship_model);

	return 0;
}