#pragma once

#include <shooting-range.hpp>

namespace sr
{
	class player
	{
	private:
		tt_vec3 m_pos={0,1.75,0}; //player/camera position


		//rocket launcher
		tt_3d_object *m_rocket_launcher=NULL;
		tt_3d_custom_model *m_rocket_launcher_model=NULL;
		tt_3d_texture *m_rocket_launcher_tex=NULL;
		tt_vec3 m_rocket_launcher_pos={0.185, -0.003, 0.20}; //rocket launcher position relative to the camera

	public:
		//fps mouse movement
		float up_angle=0;
		float side_angle=0;
		
		player();
		~player(){};
		void update();
	};
}
