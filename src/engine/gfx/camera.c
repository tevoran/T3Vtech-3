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
	tt_camera_position.array[3][0]=-position->x;
	tt_camera_position.array[3][1]=-position->y;
	tt_camera_position.array[3][2]=-position->z;
}

void tt_camera_rotate(tt_vec3 *rot_axis, float radians)
{
	tt_mat4 rot_delta_mat=tt_math_mat4_make_quat_rot_mat(rot_axis, -radians);
	tt_camera_rotation=tt_math_mat4_mul(&rot_delta_mat, &tt_camera_rotation);
}

