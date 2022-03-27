#include <tt.h>

float tt_3d_aabb_get_radius(tt_3d_collision_aabb *aabb)
{
    tt_vec3 d = tt_math_vec3_sub(&aabb->max, &aabb->min);
    return tt_math_vec3_length(&d) / 2;
}

tt_vec3 tt_3d_aabb_get_center(tt_3d_collision_aabb *aabb)
{
    tt_vec3 center = tt_math_vec3_add(&aabb->max, &aabb->min);
    center = tt_math_vec3_mul_float(&center, 0.5);
    return center;
}

bool tt_3d_sphere_collision_test(tt_3d_collision_sphere *a, tt_3d_collision_sphere *b)
{
    tt_vec3 delta = tt_math_vec3_sub(&a->origin, &b->origin);

    const float distance_sq = tt_math_vec3_length_sq(&delta);
    const float min_distance_sq = (a->r + b->r) * (a->r + b->r);

    return distance_sq <= min_distance_sq;
}
