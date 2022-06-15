#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, NULL);

    tt_gfx_phong_shading(true);
    tt_gfx_gouraud_shading(false);
    tt_gfx_tone_mapping(true);

    tt_vec3 light_col={0.5f, 0.3f, 0.03f};
    tt_vec3 light_pos={-20.0f, 10.0f, -50.0f};
    tt_point_light light=tt_point_light_new();
    tt_point_light_set_color(light, &light_col);
    tt_point_light_set_position(light, &light_pos);
    tt_point_light_set_strength(light, 2500.0f);

	tt_3d_custom_model *obj_model=tt_3d_custom_model_load_file("assets/models/ship/ship.obj");
	tt_3d_texture *obj_tex=tt_3d_texture_new("assets/models/ship/ship.bmp", true);

	const int num=10000;
	tt_3d_object *obj[num];
	for(int i=0; i<num; i++)
	{
		obj[i]=tt_3d_object_new();	
		tt_3d_object_use_texture(obj[i], obj_tex);
		tt_3d_object_use_custom_model(obj[i], obj_model);
		tt_vec3 pos={-30.0f, 0.0f, -20.0f * i};
		tt_3d_object_set_position(obj[i], &pos);
		tt_3d_object_light_affected(obj[i], false);
		tt_3d_object_make_invisible(obj[i], true);
	}

	tt_3d_batch_object *batch_object=tt_3d_batch_object_new();
	tt_3d_batch_object_batch_custom_model_objects(
		batch_object,
		obj_model,
		num,
		obj);
	tt_3d_object *batch=tt_3d_object_new();
	tt_3d_object_use_batch_object(batch, batch_object);
	tt_3d_object_light_affected(batch, true);
	tt_3d_object_use_texture(batch, obj_tex);
	tt_3d_object_add_point_light(batch, light);

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		tt_new_frame();
	}

	return 0;
}