#ifndef TT_GFX_CAMERA_H
#define TT_GFX_CAMERA_H

#include <tt.h>

void tt_gfx_camera_setup();

//user functions
void tt_camera_set_position(tt_vec3 *position);
tt_vec3 tt_camera_get_position();
void tt_camera_rotate(tt_vec3 *rot_axis, float radians);
tt_vec3 tt_camera_view_direction();
void tt_camera_fps(float pitch_radians, float yaw_radians);

#endif
