#include <shooting-range.hpp>

sr::world::world()
{
	m_range=tt_3d_object_new();
	m_range_model=tt_3d_custom_model_load_file("assets/shooting-range/range.obj");
	m_range_tex=tt_3d_texture_new("assets/shooting-range/concrete.png", true);

	tt_3d_object_use_custom_model(m_range, m_range_model);
	tt_3d_object_use_texture(m_range, m_range_tex);

	tt_vec3 scale={30,30,30};
	tt_3d_object_scale(m_range, &scale);

	//lighting
	int sun=tt_directional_light_new();
	tt_vec3 sun_dir={-0.5, -1, 0};
	tt_directional_light_set_direction(sun, &sun_dir);
	tt_vec3 sun_color={1.0, 0.98, 0.82};
	tt_directional_light_set_color(sun, &sun_color);
	tt_directional_light_set_strength(sun, 0.8);
}