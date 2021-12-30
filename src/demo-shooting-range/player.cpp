#include <player.hpp>
#include <shooting-range.hpp>

#define PLAYER_SPEED 6.6
#define PLAYER_JUMP_SPEED 0.42
#define PLAYER_HEIGHT 1.75

sr::player::player()
{
	//load rocket launcher
	m_rocket_launcher=tt_3d_object_new();
	m_rocket_launcher_model=tt_3d_custom_model_load_file("assets/shooting-range/rocket_launcher.obj");
	m_rocket_launcher_tex=tt_3d_texture_new("assets/shooting-range/rocket_launcher_tex.png", true);
	tt_3d_object_use_custom_model(m_rocket_launcher, m_rocket_launcher_model);
	tt_3d_object_use_texture(m_rocket_launcher, m_rocket_launcher_tex);

	//set starting transformations
	tt_vec3 rot_axis={1,0,0};
	tt_3d_object_rotate(m_rocket_launcher, &rot_axis, 1.5*tt_PI);
	tt_vec3 scale={0.3, 0.3, 0.3};
	tt_3d_object_scale(m_rocket_launcher, &scale);

	//prepare rockets
	m_rocket_model=tt_3d_custom_model_load_file("assets/shooting-range/rocket.obj");
	m_rocket_tex=tt_3d_texture_new("assets/shooting-range/rocket_tex.png", false);

	tt_camera_set_position(&m_pos);
}

void sr::player::update()
{
	//camera reset 
	tt_vec3 rot_axis={0,1,0};
	tt_camera_rotate(&rot_axis, -side_angle);

	rot_axis.x=1;
	rot_axis.y=0;
	rot_axis.z=0;
	tt_camera_rotate(&rot_axis, -up_angle);

	//reset rocket launcher rotation
	rot_axis.x=1;
	rot_axis.y=0;
	rot_axis.z=0;
	tt_3d_object_rotate(m_rocket_launcher, &rot_axis, -up_angle);

	rot_axis.x=0;
	rot_axis.y=0;
	rot_axis.z=1;
	tt_3d_object_rotate(m_rocket_launcher, &rot_axis, -side_angle);

	//mouse movement
	int mouse_x_rel=0;
	int mouse_y_rel=0;
	tt_input_mouse_relative_motion(&mouse_x_rel, &mouse_y_rel);
	side_angle+=0.001*mouse_x_rel;
	up_angle+=0.001*mouse_y_rel;
	
	//blocking angle is player looks above or below
	if(up_angle>0.5*tt_PI)
	{
		up_angle=0.5*tt_PI;
	}
	if(up_angle<-0.5*tt_PI)
	{
		up_angle=-0.5*tt_PI;
	}

	//keyboard movement
	float t_delta=tt_time_current_frame_s();
	if(tt_input_keyboard_key_pressed(TT_KEY_W))
	{
		m_pos.z+=cos(side_angle) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle) * PLAYER_SPEED * t_delta;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_S))
	{
		m_pos.z-=cos(side_angle) * PLAYER_SPEED * t_delta;
		m_pos.x-=sin(side_angle) * PLAYER_SPEED * t_delta;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_D))
	{
		m_pos.z+=cos(side_angle + 0.5*tt_PI) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle + 0.5*tt_PI) * PLAYER_SPEED * t_delta;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_A))
	{
		m_pos.z+=cos(side_angle - 0.5*tt_PI) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle - 0.5*tt_PI) * PLAYER_SPEED * t_delta;
	}

	//jumping
	static bool in_air=false;
	static float y_vel=0;
	if(tt_input_keyboard_key_pressed(TT_KEY_SPACE) && in_air==false)
	{
		in_air=true;
		y_vel=PLAYER_JUMP_SPEED;
	}
	if(in_air)
	{
		m_pos.y+=y_vel;
		y_vel-=WORLD_GRAVITY * t_delta;
	}
	if(m_pos.y<PLAYER_HEIGHT)
	{
		m_pos.y=PLAYER_HEIGHT;
		in_air=false;
	}

	//leave player inside the world
	if(m_pos.z>WORLD_Z_BORDER)
	{
		m_pos.z=WORLD_Z_BORDER;
	}
	if(m_pos.z<-WORLD_Z_BORDER)
	{
		m_pos.z=-WORLD_Z_BORDER;
	}
	if(m_pos.x>WORLD_X_BORDER)
	{
		m_pos.x=WORLD_X_BORDER;
	}
	if(m_pos.x<-WORLD_X_BORDER)
	{
		m_pos.x=-WORLD_X_BORDER;
	}

	tt_camera_set_position(&m_pos);

	//rotate camera in a fps style
	rot_axis.x=1;
	rot_axis.y=0;
	rot_axis.z=0;
	tt_camera_rotate(&rot_axis, up_angle);

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	tt_camera_rotate(&rot_axis, side_angle);


	//rotate rocket launcher
	rot_axis.x=0;
	rot_axis.y=0;
	rot_axis.z=1;
	tt_3d_object_rotate(m_rocket_launcher, &rot_axis, side_angle );

	rot_axis.x=1;
	rot_axis.y=0;
	rot_axis.z=0;
	tt_3d_object_rotate(m_rocket_launcher, &rot_axis, up_angle);

	//update rocket launcher position
	rot_axis.x=1;
	rot_axis.y=0;
	rot_axis.z=0;
	tt_vec3 r_l_pos_abs = tt_math_vec3_rotate(&rot_axis, up_angle, &m_rocket_launcher_pos);
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;

	r_l_pos_abs = tt_math_vec3_rotate(&rot_axis, side_angle, &r_l_pos_abs);
	r_l_pos_abs = tt_math_vec3_add(&r_l_pos_abs, &m_pos);
	tt_3d_object_set_position(m_rocket_launcher, &r_l_pos_abs);

	tt_vec3 view_dir=tt_camera_view_direction();
	//std::cout << view_dir.x << " " << view_dir.y << " " << view_dir.z << std::endl;

	//shoot rockets
	static float rocket_delay=0;

	if(tt_input_keyboard_key_pressed(TT_KEY_SPACE) && rocket_delay==0)
	{
		rocket_delay=1.0;
		tt_vec3 view_dir=tt_camera_view_direction();

		std::unique_ptr<rocket> tmp_rocket(new rocket(
			m_rocket_model,
			m_rocket_tex,
			m_rocket_launcher,
			m_pos,
			view_dir));

		m_rockets.emplace_back(std::move(tmp_rocket));
	}
	rocket_delay-=t_delta;
	if(rocket_delay<0)
	{
		rocket_delay=0;
	}

	//std::cout << m_rockets.size() << std::endl;

	//update all the rockets
	for(int i=0; i<m_rockets.size(); i++)
	{
		if(!m_rockets[i]->update()) //if returns false then it is ready to be destroyed
		{
			//delete m_rockets[i];
			m_rockets.erase(m_rockets.begin() + i);
		}	
	}
}