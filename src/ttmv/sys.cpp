#include <ttmv.hpp>

ttmv::sys::sys(int argc, char *argv[])
{
	if(argc==2 || argc==3)
	{
		tt_init("TTMV", 1366,768, false, 4, true);
		//load only model
		model=tt_3d_object_new();
		custom_model=tt_3d_custom_model_load_file(argv[1]);
		if(custom_model==NULL)
		{
			exit(EXIT_FAILURE);
		}
		tt_3d_object_use_custom_model(model, custom_model);
		tt_vec3 pos=
		{
			0,
			0,
			tt_3d_object_get_bounding_sphere_size(model)
		};
		tt_3d_object_set_position(model, &pos);
		
		tt_ambient_light_set_strength(0.3);
		int light=tt_directional_light_new();
		tt_vec3 light_dir={-1,0,1};
		tt_directional_light_set_direction(light, &light_dir);
		tt_directional_light_set_strength(light, 0.9);

		//load texture as well
		if(argc==3)
		{
			tex=tt_3d_texture_new(argv[2], true);
			tt_3d_object_use_texture(model, tex);
		}
	}
	else
	{
		std::cout << "[ERROR] wrong amount of parameters set\n";
		exit(EXIT_FAILURE);
	}
}

ttmv::sys::~sys()
{
	if(tex)
	{
		tt_3d_texture_delete(&tex);
	}
	tt_3d_custom_model_delete(&custom_model);
	tt_3d_object_delete(&model);
}

void ttmv::sys::loop(int max_frames)
{
	tt_vec3 rot_axis={0.2, 1, 0.05};
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		tt_3d_object_rotate(model, &rot_axis, rot_speed);
		tt_new_frame();
	}
}
