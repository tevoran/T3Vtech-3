#include <ttmv.hpp>

ttmv::sys::sys(int argc, char *argv[])
{
	if(argc==2 || argc==3)
	{
		tt_init("TTMV", 720,720, false, true);
		//load only model
		model=tt_3d_object_new();
		custom_model=tt_3d_custom_model_load_file(argv[1]);
		tt_3d_object_use_custom_model(model, custom_model);
		tt_vec3 pos={0,0,20};
		tt_3d_object_set_position(model, &pos);
		tt_ambient_light_set_strength(1.0);

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
