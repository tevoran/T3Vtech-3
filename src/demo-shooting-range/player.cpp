#include <player.hpp>
#include <shooting-range.hpp>

#define PLAYER_SPEED 0.11
#define PLAYER_JUMP_SPEED 0.42
#define PLAYER_HEIGHT 1.75

sr::player::player()
{
	tt_camera_set_position(&m_pos);
}

void sr::player::update()
{
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
	if(tt_input_keyboard_key_pressed(TT_KEY_W))
	{
		m_pos.z+=cos(side_angle) * PLAYER_SPEED;
		m_pos.x+=sin(side_angle) * PLAYER_SPEED;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_S))
	{
		m_pos.z-=cos(side_angle) * PLAYER_SPEED;
		m_pos.x-=sin(side_angle) * PLAYER_SPEED;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_D))
	{
		m_pos.z+=cos(side_angle + 0.5*tt_PI) * PLAYER_SPEED;
		m_pos.x+=sin(side_angle + 0.5*tt_PI) * PLAYER_SPEED;
	}
	if(tt_input_keyboard_key_pressed(TT_KEY_A))
	{
		m_pos.z+=cos(side_angle - 0.5*tt_PI) * PLAYER_SPEED;
		m_pos.x+=sin(side_angle - 0.5*tt_PI) * PLAYER_SPEED;
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
		y_vel-=WORLD_GRAVITY;
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
}