#include <shooting-range.hpp>

#define ROCKET_SPEED 45
#define EX_SPEED 10

sr::rocket::rocket(
			tt_3d_custom_model *rocket_model,
			tt_3d_texture *rocket_tex,
			tt_3d_custom_model *ex_model,
			tt_3d_texture *ex[EX_STEPS],
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
	tt_3d_object_rotate_like(m_rocket, rocket_launcher);
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	//tt_3d_object_rotate(m_rocket, &rot_axis, 1.0 * tt_PI);

	m_pos=pos_start;
	float length=tt_math_vec3_length(&dir);
	m_dir.x=dir.x/length;
	m_dir.y=dir.y/length;
	m_dir.z=dir.z/length;

	m_pos.x+=m_dir.x;
	m_pos.y+=m_dir.y;
	m_pos.z+=m_dir.z;

	//prepare the explosions
	m_ex_obj=tt_3d_object_new();
	tt_3d_object_use_custom_model(m_ex_obj, ex_model);
	tt_3d_object_light_affected(m_ex_obj, false);
	tt_3d_object_make_invisible(m_ex_obj, true);
	for(int i=0; i<EX_STEPS; i++)
	{
		m_ex[i]=ex[i];
	}
}

sr::rocket::~rocket()
{
	tt_3d_object_delete(&m_rocket);
	tt_3d_object_delete(&m_ex_obj);
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

	//if rockets leaves the space then explode
	if(	(	(m_pos.x< -WORLD_X_BORDER || m_pos.x>WORLD_X_BORDER) ||
			(m_pos.z< -WORLD_Z_BORDER || m_pos.z>WORLD_Z_BORDER) ||
			(m_pos.y< 0.75 || m_pos.y>100)) &&
		!m_exploded)
	{
		m_exploded=true;
		tt_3d_object_make_invisible(m_rocket, true);
		tt_3d_object_make_invisible(m_ex_obj, false);
		tt_3d_object_set_position(m_ex_obj, &m_pos);
	}

	//showing the explosion
	if(m_exploded)
	{
		m_scale.x += EX_SPEED * t_delta;
		m_scale.y += EX_SPEED * t_delta;
		m_scale.z += EX_SPEED * t_delta;
		tt_3d_object_scale(m_ex_obj, &m_scale);

		if(m_scale.y>0)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[0]);
		}

		if(m_scale.y>0.5)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[1]);
		}

		if(m_scale.y>1)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[2]);
		}

		if(m_scale.y>1.5)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[3]);
		}

		if(m_scale.y>2)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[4]);
		}

		if(m_scale.y>2.5)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[5]);
		}

		if(m_scale.y>3)
		{
			tt_3d_object_use_texture(m_ex_obj, m_ex[6]);
			tt_3d_object_light_affected(m_ex_obj, true);
		}

		if(m_scale.y>6)
		{
			return false;
		}
	}
	return true;
}