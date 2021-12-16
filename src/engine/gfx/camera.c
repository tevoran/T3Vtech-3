#include <tt.h>

extern tt_mat4 tt_camera_position; //current camera position

void tt_gfx_camera_setup()
{
	tt_math_mat4_make_identity_matrix(&tt_camera_position);
}

void tt_camera_set_position(tt_vec3 *position)
{
	tt_camera_position.array[3][0]=-position->x;
	tt_camera_position.array[3][1]=-position->y;
	tt_camera_position.array[3][2]=-position->z;
}