#ifndef TT_GFX_LIGHTING_H
#define TT_GFX_LIGHTING_H

#include <tt.h>


void tt_gfx_gouraud_shading(bool active);

//ambient light
void tt_ambient_light_set_strength(float strength);
void tt_ambient_light_set_color(tt_vec3 *color);

//directional light
void tt_gfx_directional_light_setup();
void tt_gfx_directional_light_cleanup();

int tt_directional_light_new();
void tt_directional_light_delete(int light_id);
void tt_directional_light_set_direction(int light_id, tt_vec3 *direction);
void tt_directional_light_set_strength(int light_id, float strength);
void tt_directional_light_set_color(int light_id, tt_vec3 *color);

//point light
void tt_gfx_point_light_setup();
void tt_gfx_point_light_cleanup();

int tt_point_light_new(tt_vec3 *position, tt_vec3 *color);
void tt_point_light_set_strength(int light_id, float strength);
void tt_point_light_set_color(int light_id, tt_vec3 *color);
void tt_point_light_set_position(int light_id, tt_vec3 *position);

#endif