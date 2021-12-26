#pragma once

#include <tt.h>
#include <world.hpp>
#include <player.hpp>
#include <iostream>

namespace sr
{
	class sr
	{
	private:
		world *m_range=NULL;

	public:
		void update(const float side_angle, const float up_angle);
		sr();
		~sr();
	};
}