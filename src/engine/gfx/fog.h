#ifndef TT_GFX_FOG_H
#define TT_GFX_FOG_H

#include <tt.h>

extern bool tt_gfx_fog_active; //toggle if fog is used
extern tt_vec3 tt_gfx_fog_color; //default fog color
extern float tt_gfx_fog_max_distance; //max fog distance (1.0 is the max drawing distance)
extern float tt_gfx_fog_min_distance; //min fog distance (1.0 is the max drawing distance)
extern float tt_far_plane; //far clipping plane

void tt_gfx_fog_set_active(bool fog_active);
void tt_gfx_fog_set_color(const tt_vec3 *fog_color);
void tt_gfx_fog_set_max_distance(float distance);
void tt_gfx_fog_set_min_distance(float distance);


#endif