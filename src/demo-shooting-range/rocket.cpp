#include <shooting-range.hpp>

#define ROCKET_SPEED 0.2

sr::rocket::rocket(
			tt_3d_custom_model *rocket_model,
			tt_3d_texture *rocket_tex,
			tt_3d_object *rocket_launcher,
			tt_vec3& pos_start,
			tt_vec3& dir)
{
	//prepare the model
	m_rocket=tt_3d_object_new();
	tt_3d_object_use_custom_model(m_rocket, rocket_model);
	tt_3d_object_use_texture(m_rocket, rocket_tex);
	tt_vec3 scale={0.2,0.2,0.2};
	tt_3d_object_scale(m_rocket, &scale);
	tt_vec3 rot_axis={1,0,0};
	tt_3d_object_rotate(m_rocket, &rot_axis, 0.5 * tt_PI);
	tt_3d_object_rotate_like(rocket_launcher, m_rocket);
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	//tt_3d_object_rotate(m_rocket, &rot_axis, 1.0 * tt_PI);

	m_pos=pos_start;
	float length=tt_math_vec3_length(dir);
	m_dir.x=dir.x/length;
	m_dir.y=dir.y/length;
	m_dir.z=dir.z/length;
}

sr::rocket::~rocket()
{
	//std::cout << "dod\n";
	tt_3d_object_delete(&m_rocket);
}

//true if rocket should still live
//false if ready to be destroyed
bool sr::rocket::update()
{
	float t_delta=tt_time_current_frame_s();

	m_pos.x+=m_dir.x * ROCKET_SPEED * t_delta;
	m_pos.y+=m_dir.y * ROCKET_SPEED * t_delta;
	m_pos.z+=m_dir.z * ROCKET_SPEED * t_delta;

	//std::cout << m_pos.x << " " << m_pos.y << " " << m_pos.z << std::endl;
	tt_3d_object_set_position(m_rocket, &m_pos);

	return true;
}