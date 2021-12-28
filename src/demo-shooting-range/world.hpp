#pragma once

#include <tt.h>
#include <shooting-range.hpp>

#define WORLD_Z_BORDER 78.0
#define WORLD_X_BORDER 107.0
#define WORLD_GRAVITY 0.9

namespace sr
{
	class world
	{
	private:
		//shooting range
		tt_3d_object *m_range=NULL;
		tt_3d_custom_model *m_range_model=NULL;
		tt_3d_texture *m_range_tex=NULL;

		//skybox
		tt_3d_object *m_sky=NULL;
		tt_3d_custom_model *m_sky_model=NULL;
		tt_3d_texture *m_sky_tex=NULL;

	public:
		world();
		~world(){};
	};
}
