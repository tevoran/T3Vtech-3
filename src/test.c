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

	//text test
	tt_font *font=tt_font_open("assets/fonts/OpenSans-Regular.ttf", 100);
	tt_2d_object *text_obj=tt_2d_object_new();
	//tt_2d_object_make_sprite(text_obj);
	tt_2d_object_make_text(text_obj,font,"poopy text");

	//sprite test
	unsigned char test_tex[]=
	{
		0, 0, 0, 0,	 		0, 255, 0, 255,		0, 0, 0, 0,
		0, 255, 0, 255,		0, 0, 0, 0,		0, 255, 0, 255,
		0, 0, 0, 0,			0, 0, 0, 0,		0, 0, 0, 0,
	};

	tt_2d_object *sprite=tt_2d_object_new();
	tt_2d_object_make_sprite(sprite);
	tt_2d_texture* sprite_tex=tt_2d_texture_new_from_RGBA(
		test_tex, 
		3,
		3,
		false);

	//tt_2d_object_use_texture(text_obj, sprite_tex);

	tt_2d_object_use_texture(sprite, sprite_tex);
	//tt_2d_object_delete(&sprite);

	tt_vec2 sprite_pos={0.0,0.0};

	tt_2d_object *sprite2=tt_2d_object_new();
	tt_2d_object_make_sprite(sprite2);
	tt_vec2 sprite_scale={0.3,0.3};
	tt_2d_object_scale(sprite2, &sprite_scale);


	float angle=0.0;
	int i=0;
	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
	i++;

	//sprite test
	angle+=0.01;
	sprite_pos.x=0.5*sin((float)i/200);
	tt_2d_object_set_position(sprite, &sprite_pos);
	tt_2d_object_render(sprite2);
	tt_2d_object_render(sprite);
	tt_2d_object_rotate(sprite2, angle);
	tt_2d_object_render(text_obj);


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

	tt_font_delete(&font);

	return 0;
}