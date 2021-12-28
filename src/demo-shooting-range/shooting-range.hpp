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
		void update();
		sr();
		~sr();
	};
}