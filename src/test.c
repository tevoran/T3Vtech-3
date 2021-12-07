#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 768, true);

	float fov=0.5*tt_PI;
	tt_vec3 pos={0.0,0.0,5.0};
	tt_vec3 scale={1,1,1};
	tt_vec3 orientation={0.5,0.5,0.0};
	tt_3d_object *cube=tt_3d_object_new();

	tt_3d_object_set_position(cube, &pos);

	tt_vec3 rot_axis={1,1,0};

	tt_3d_custom_model *model=tt_3d_custom_model_load_file("assets/models/box/box.obj");
	tt_3d_texture *tex=tt_3d_texture_new("assets/models/box/box.png", true);
	tt_3d_object_use_texture(cube, tex);
	tt_3d_object_use_custom_model(cube, model);


	for(int i=0; i<1000; i++)
	{
		tt_new_frame();
		//SDL_Delay(15);

		tt_3d_object_rotate(cube, &rot_axis, 0.02);

	}

	//tt_3d_texture_delete(&tex);

	return 0;
}