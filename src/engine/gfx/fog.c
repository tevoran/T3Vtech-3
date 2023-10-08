#include "fog.h"

void tt_gfx_fog_set_active(bool fog_active)
{
    tt_gfx_fog_active=fog_active;
};

void tt_gfx_fog_set_color(const tt_vec3 *fog_color)
{
    tt_gfx_fog_color=*fog_color;
};

void tt_gfx_fog_set_max_distance(float distance)
{
    tt_gfx_fog_max_distance = distance/tt_far_plane;
}

void tt_gfx_fog_set_min_distance(float distance)
{
    tt_gfx_fog_min_distance = distance/tt_far_plane;
}