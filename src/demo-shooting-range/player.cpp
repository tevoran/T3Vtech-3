#include <player.hpp>
#include <shooting-range.hpp>

#define PLAYER_SPEED 0.08;

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
	tt_camera_set_position(&m_pos);
}