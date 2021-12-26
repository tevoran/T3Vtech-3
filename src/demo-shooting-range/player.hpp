#pragma once

#include <shooting-range.hpp>

namespace sr
{
	class player
	{
	private:
		tt_vec3 m_pos={0,1.75,0};

	public:
		//fps mouse movement
		float up_angle=0;
		float side_angle=0;
		
		player();
		~player(){};
		void update();
	};
}
