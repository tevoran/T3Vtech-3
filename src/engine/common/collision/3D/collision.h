#ifndef TT_GFX_3D_COLLISION_H
#define TT_GFX_3D_COLLISION_H

#include <tt.h>

struct tt_3d_collision_aabb
{
	tt_vec3 min;
	tt_vec3 max;
} typedef tt_3d_collision_aabb;

struct tt_3d_collision_sphere
{
	tt_vec3 origin;
	float r;
} typedef tt_3d_collision_sphere;

float tt_3d_aabb_get_radius(tt_3d_collision_aabb *aabb);
tt_vec3 tt_3d_aabb_get_center(tt_3d_collision_aabb *aabb);

bool tt_3d_sphere_collision_test(tt_3d_collision_sphere *a, tt_3d_collision_sphere *b);

#endif
