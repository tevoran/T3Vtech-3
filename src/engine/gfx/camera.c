#include <tt.h>

extern tt_mat4 tt_camera_position; //current camera position
extern tt_mat4 tt_camera_rotation; //current camera rotation


void tt_gfx_camera_setup()
{
	tt_math_mat4_make_identity_matrix(&tt_camera_position);
	tt_math_mat4_make_identity_matrix(&tt_camera_rotation);
}

void tt_camera_set_position(tt_vec3 *position)
{
	tt_camera_position.array[0][3]=-position->x;
	tt_camera_position.array[1][3]=-position->y;
	tt_camera_position.array[2][3]=-position->z;
}

tt_vec3 tt_camera_get_position()
{
	tt_vec3 out;
	out.x=-tt_camera_position.array[0][3];
	out.y=-tt_camera_position.array[1][3];
	out.z=-tt_camera_position.array[2][3];
	return out;
}

void tt_camera_rotate(tt_vec3 *rot_axis, float radians)
{
	tt_mat4 rot_delta_mat=tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
	tt_camera_rotation=tt_math_mat4_mul(&rot_delta_mat, &tt_camera_rotation);
}

tt_vec3 tt_camera_view_direction()
{
	tt_vec3 start_dir={0,0,-1}; //along the -z-axis
	tt_mat4 tmp_mat;
	tt_math_mat4_make_identity_matrix(&tmp_mat);
	tmp_mat.array[0][3]=start_dir.x;
	tmp_mat.array[1][3]=start_dir.y;
	tmp_mat.array[2][3]=start_dir.z;

	tt_mat4 inv_mat=tt_math_mat4_transpose(&tt_camera_rotation);
	tmp_mat=tt_math_mat4_mul(&inv_mat, &tmp_mat);
	tt_vec3 out=
	{
		tmp_mat.array[0][3],
		tmp_mat.array[1][3],
		tmp_mat.array[2][3],
	};
	return out;
}

void tt_camera_fps(float pitch_radians, float yaw_radians)
{
	tt_vec3 pitch_axis = {1,0,0};
	tt_vec3 yaw_axis = { 0,1,0 };

	tt_math_mat4_make_identity_matrix(&tt_camera_rotation);

	tt_camera_rotate(&pitch_axis, pitch_radians);
	tt_camera_rotate(&yaw_axis, yaw_radians);

	tt_camera_rotation.array[0][2] *= -1;
	tt_camera_rotation.array[1][2] *= -1;
	tt_camera_rotation.array[2][2] *= -1;

	tt_camera_rotation.array[0][0] *= -1;
	tt_camera_rotation.array[1][0] *= -1;
	tt_camera_rotation.array[2][0] *= -1;

	tt_camera_rotation = tt_math_mat4_transpose(&tt_camera_rotation);
}
