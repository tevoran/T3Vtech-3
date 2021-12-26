#pragma once

#include <tt.h>
#include <shooting-range.hpp>

namespace sr
{
	class world
	{
	private:
		tt_3d_object *m_range=NULL;
		tt_3d_custom_model *m_range_model=NULL;
		tt_3d_texture *m_range_tex=NULL;

	public:
		world();
		~world(){};
	};
}
