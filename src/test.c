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

	tt_3d_object_light_affected(ship, false);

	for(int i=0; i<2000; i++)
	{
		tt_new_frame();
		//SDL_Delay(15);

		//tt_vec3 light_direction={sin((float)i/60),0.0,cos((float)i/60)};
		//tt_gfx_set_light_direction(&light_direction);
		if(i==100)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={-1,0,0};
			tt_vec3 light_color={0, 1, 0};
			tt_directional_light_set_direction(1, &light_direction);
			tt_directional_light_set_strength(1, 0.1);
			tt_directional_light_set_color(1, &light_color);
		}
		if(i==300)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={1,1,-1};
			tt_vec3 light_color={1, 1, 0};
			tt_directional_light_set_direction(2, &light_direction);
			tt_directional_light_set_strength(2, 0.1);
			tt_directional_light_set_color(2, &light_color);
		}
		if(i==500)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={-1,2,-1};
			tt_vec3 light_color={1, 1, 1};
			tt_directional_light_set_direction(3, &light_direction);
			tt_directional_light_set_strength(3, 0.1);
			tt_directional_light_set_color(3, &light_color);
		}
		if(i==700)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={1,1,1};
			tt_vec3 light_color={1, 0.1, 1};
			tt_directional_light_set_direction(4, &light_direction);
			tt_directional_light_set_strength(4, 0.5);
			tt_directional_light_set_color(4, &light_color);
		}
		if(i==900)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={1,-1,-1};
			tt_vec3 light_color={0.3, 0.5, 0};
			tt_directional_light_set_direction(5, &light_direction);
			tt_directional_light_set_strength(5, 0.4);
			tt_directional_light_set_color(5, &light_color);
		}
		if(i==1100)
		{
			printf("light: %i\n",tt_directional_light_new());
			tt_vec3 light_direction={0,1,-0.1};
			tt_vec3 light_color={1, 1, 1};
			tt_directional_light_set_direction(6, &light_direction);
			tt_directional_light_set_strength(6, 0.1);
			tt_directional_light_set_color(6, &light_color);
		}
	}

	tt_3d_texture_delete(&ship_tex);
	tt_3d_custom_model_delete(&ship_model);

	return 0;
}