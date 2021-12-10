#ifndef TT_GFX_LIGHTING_H
#define TT_GFX_LIGHTING_H

#include <tt.h>


void tt_gfx_gouraud_shading(bool active);

//directional light
void tt_gfx_set_light_direction(tt_vec3 *direction);
void tt_gfx_set_light_direction_color(tt_vec3 *color);
void tt_gfx_set_light_direction_strength(float strength);



#endif