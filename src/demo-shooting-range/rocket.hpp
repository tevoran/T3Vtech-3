#pragma once

#include <shooting-range.hpp>

namespace sr
{
	class rocket
	{
	private:
		tt_3d_object *m_rocket=NULL;
		tt_3d_object *m_ex_obj=NULL;
		tt_3d_texture *m_ex[EX_STEPS];
		tt_vec3 m_pos;
		tt_vec3 m_dir;

		//explosion effects
		bool m_exploded=false;
		tt_vec3 m_scale={0.0,0.0,0.0};
	public:
		rocket(
			tt_3d_custom_model *rocket_model,
			tt_3d_texture *rocket_tex,
			tt_3d_custom_model *ex_model,
			tt_3d_texture *ex[EX_STEPS],
			tt_3d_object *rocket_launcher,
			tt_vec3& pos_start,
			tt_vec3& dir);
		bool update();
		~rocket();
	};
}