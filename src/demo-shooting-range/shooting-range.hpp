#pragma once

#include <tt.h>
#include <memory>
#include <world.hpp>
#include <player.hpp>
#include <rocket.hpp>
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