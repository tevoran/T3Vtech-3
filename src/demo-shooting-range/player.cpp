#include <player.hpp>
#include <shooting-range.hpp>

#define PLAYER_SPEED 6.6
#define PLAYER_JUMP_SPEED 0.3
#define PLAYER_HEIGHT 1.75

#define CTL_NUM 1

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

	//prepare explosions
	m_ex_model=tt_3d_custom_model_load_file("assets/shooting-range/explosion.obj");
	m_ex[0]=tt_3d_texture_new("assets/shooting-range/ex_00.png", false);
	m_ex[1]=tt_3d_texture_new("assets/shooting-range/ex_01.png", false);
	m_ex[2]=tt_3d_texture_new("assets/shooting-range/ex_02.png", false);
	m_ex[3]=tt_3d_texture_new("assets/shooting-range/ex_03.png", false);
	m_ex[4]=tt_3d_texture_new("assets/shooting-range/ex_04.png", false);
	m_ex[5]=tt_3d_texture_new("assets/shooting-range/ex_05.png", false);
	m_ex[6]=tt_3d_texture_new("assets/shooting-range/ex_06.png", false);

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

	//controller axis movement
	float l_stick_x=0;
	float l_stick_y=0;
	float r_stick_x=0;
	float r_stick_y=0;
	tt_input_controller_axis_state(
		CTL_NUM,
		&l_stick_x,
		&l_stick_y,
		&r_stick_x,
		&r_stick_y);
	side_angle+=0.02*r_stick_x;
	up_angle+=0.02*r_stick_y;

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

	//moving around with keys/buttons
	float t_delta=tt_time_current_frame_s();
	if(	tt_input_keyboard_key_down(TT_KEY_W) ||
		tt_input_controller_button_down(CTL_NUM, TT_CTL_UP))
	{
		m_pos.z+=cos(side_angle) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle) * PLAYER_SPEED * t_delta;
	}
	if(	tt_input_keyboard_key_down(TT_KEY_S) ||
		tt_input_controller_button_down(CTL_NUM, TT_CTL_DOWN))
	{
		m_pos.z-=cos(side_angle) * PLAYER_SPEED * t_delta;
		m_pos.x-=sin(side_angle) * PLAYER_SPEED * t_delta;
	}
	if(	tt_input_keyboard_key_down(TT_KEY_D) ||
		tt_input_controller_button_down(CTL_NUM, TT_CTL_RIGHT))
	{
		m_pos.z+=cos(side_angle + 0.5*tt_PI) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle + 0.5*tt_PI) * PLAYER_SPEED * t_delta;
	}
	if(	tt_input_keyboard_key_down(TT_KEY_A) ||
		tt_input_controller_button_down(CTL_NUM, TT_CTL_LEFT))
	{
		m_pos.z+=cos(side_angle - 0.5*tt_PI) * PLAYER_SPEED * t_delta;
		m_pos.x+=sin(side_angle - 0.5*tt_PI) * PLAYER_SPEED * t_delta;
	}

	//moving around with analog sticks
	//forward
	m_pos.z-=cos(side_angle) * PLAYER_SPEED * t_delta * l_stick_y;
	m_pos.x-=sin(side_angle) * PLAYER_SPEED * t_delta * l_stick_y;

	//sidewards
	m_pos.z-=cos(side_angle - 0.5 * tt_PI) * PLAYER_SPEED * t_delta * l_stick_x;
	m_pos.x-=sin(side_angle - 0.5 * tt_PI) * PLAYER_SPEED * t_delta * l_stick_x;

	//jumping
	static bool in_air=false;
	static float y_vel=0;
	if(	(tt_input_keyboard_key_down(TT_KEY_SPACE) ||
		tt_input_controller_button_down(CTL_NUM, TT_CTL_A) )
		&& in_air==false)
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

	if((tt_input_mouse_button_press(TT_MOUSE_LEFT) ||
		tt_input_controller_button_press(CTL_NUM, TT_CTL_RSHOULDER))
		&& rocket_delay==0)
	{
		rocket_delay=0.0;
		tt_vec3 view_dir=tt_camera_view_direction();

		std::unique_ptr<rocket> tmp_rocket(new rocket(
			m_rocket_model,
			m_rocket_tex,
			m_ex_model,
			m_ex,
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