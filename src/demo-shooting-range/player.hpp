#pragma once

#include <shooting-range.hpp>

namespace sr
{
	class player
	{
	private:
		tt_vec3 m_pos={0,1.75,0};
	public:
		player();
		~player(){};
	};
}
