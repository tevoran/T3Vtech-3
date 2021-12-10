#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 768, true);

	float fov=0.5*tt_PI;
	tt_vec3 pos={0.0,0.0,17.0};
	tt_vec3 scale={1,1,1};
	tt_vec3 orientation={0.5,0.5,0.0};
	tt_3d_object *ship=tt_3d_object_new();
	tt_3d_object *quad=tt_3d_object_new();

	tt_3d_object_set_position(ship, &pos);

	tt_vec3 rot_axis={1,1,0};

	tt_3d_custom_model *ship_model=tt_3d_custom_model_load_file("assets/models/ship/ship.obj");
	tt_3d_texture *ship_tex=tt_3d_texture_new("assets/models/ship/ship.bmp", false);
	tt_3d_object_use_texture(ship, ship_tex);
	tt_3d_object_use_custom_model(ship, ship_model);


	for(int i=0; i<4000; i++)
	{
		tt_new_frame();
		//SDL_Delay(15);

		tt_3d_object_rotate(ship, &rot_axis, 0.02);

	}

	tt_3d_texture_delete(&ship_tex);
	tt_3d_custom_model_delete(&ship_model);

	return 0;
}