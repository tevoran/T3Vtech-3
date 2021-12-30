#pragma once

#include <shooting-range.hpp>

namespace sr
{
	class rocket
	{
	private:
		tt_3d_object *m_rocket=NULL;
		tt_vec3 m_pos;
		tt_vec3 m_dir;
	public:
		rocket(
			tt_3d_custom_model *rocket_model,
			tt_3d_texture *rocket_tex,
			tt_3d_object *rocket_launcher,
			tt_vec3& pos_start,
			tt_vec3& dir);
		bool update();
		~rocket();
	};
}