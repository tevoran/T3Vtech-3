#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, false);


	tt_3d_object *cube=tt_3d_object_new();
	tt_3d_object_make_cube(cube);
	tt_vec3 cube_pos={0,0,4};
	tt_3d_object_set_position(cube, &cube_pos);

	tt_3d_texture *crate=tt_3d_texture_new("assets/smiley.png", false);
	tt_3d_object_use_texture(cube, crate);

	//collision test
	tt_3d_custom_model *col_model=tt_3d_custom_model_load_file("assets/models/ship/ship.obj");
	tt_3d_object *col_cube=tt_3d_object_new();
	//tt_3d_object_make_cube(col_cube);
	tt_3d_object_use_custom_model(col_cube, col_model);
	cube_pos.y=1.5;
	tt_3d_object_set_position(col_cube, &cube_pos);
	tt_vec3 col_scale={0.1,0.1,0.1};
	tt_3d_object_scale(col_cube, &col_scale);

	tt_2d_object *col_txt=tt_2d_object_new();
	tt_2d_object_make_sprite(col_txt);

	tt_font *font=tt_font_open("assets/fonts/OpenSans-Light.ttf", 100);
	tt_color_rgba_u8 txt_color={255,255,255,255};
	tt_2d_texture *col_txt_tex=tt_2d_texture_make_text(font, "COLLIDING", txt_color);
	tt_2d_object_use_texture(col_txt, col_txt_tex);
	tt_vec2 col_txt_pos={-0.90,0.95};
	tt_vec2 col_txt_scale={0.2,0.1};
	tt_2d_object_scale(col_txt, &col_txt_scale);
	tt_2d_object_set_position(col_txt, &col_txt_pos);

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

	//fps cam test
	tt_input_mouse_set_relative_mode(true);

	//test data
	int16_t data[22000*10];
	for(int i=0; i<22000*10; i++)
	{
		data[i]=sin((float)i/3500)*INT_MAX;
	}

	//audio test
	tt_3d_audio_source *source=tt_audio_3d_source_new();
	tt_sound *sound=tt_audio_sound_from_file("assets/audio/test-moo.wav");
	tt_audio_buffer_sound_for_3d_source(sound,source);
	tt_audio_play_3d_source(source);
	tt_audio_loop_3d_source(source, true);

	float angle=0.0;
	int i=0;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		i++;

		//collision test
		//cube_pos.y-=0.005;
		tt_3d_object_set_position(col_cube, &cube_pos);

		tt_vec3 col_rot_axis={1,0,0};
		tt_3d_object_rotate(col_cube, &col_rot_axis, 0.02);

		if(tt_3d_object_colliding_aabb(cube, col_cube))
		{
			tt_2d_object_render(col_txt);
		}

		//fps cam test
		static float roll_radians=0;
		static float pitch_radians=0;

		int dx, dy;
		float time=tt_time_current_frame_s();
		tt_input_mouse_relative_motion(&dx, &dy);
		roll_radians+=(float)dy * time * 0.02;
		pitch_radians+=(float)dx * time * 0.02;
		tt_camera_fps(roll_radians, pitch_radians);

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