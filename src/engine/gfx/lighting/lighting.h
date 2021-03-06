#ifndef TT_GFX_LIGHTING_H
#define TT_GFX_LIGHTING_H

#define TT_NO_LIGHT 0xFFFFFFFF

#include <tt.h>

typedef int tt_point_light;
typedef int tt_dir_light;
typedef int tt_ao_light;

void tt_gfx_gouraud_shading(bool active);
void tt_gfx_phong_shading(bool active);
void tt_gfx_tone_mapping(bool active);
void tt_gfx_set_exposure(float exposure);
void tt_gfx_set_saturation(float saturation);
void tt_gfx_set_contrast(float contrast);

//ambient light
void tt_ambient_light_set_strength(float strength);
void tt_ambient_light_set_color(tt_vec3 *color);

//directional light
void tt_gfx_directional_light_setup();
void tt_gfx_directional_light_cleanup();
void tt_gfx_directional_light_update_ubo();

tt_dir_light tt_directional_light_new();
void tt_directional_light_delete(tt_dir_light light_id);
void tt_directional_light_set_direction(tt_dir_light light_id, tt_vec3 *direction);
void tt_directional_light_set_strength(tt_dir_light light_id, float strength);
void tt_directional_light_set_color(tt_dir_light light_id, tt_vec3 *color);

//point light
void tt_gfx_point_light_setup();
void tt_gfx_point_light_cleanup();
void tt_gfx_point_light_update_ubo();

tt_point_light tt_point_light_new();
void tt_point_light_delete(tt_point_light light_id);
void tt_point_light_set_strength(tt_point_light light_id, float strength);
void tt_point_light_set_color(tt_point_light light_id, tt_vec3 *color);
void tt_point_light_set_position(tt_point_light light_id, tt_vec3 *position);
int tt_point_light_get_gpu_index(tt_point_light light_id);

//ao light
void tt_gfx_ao_light_setup();
void tt_gfx_ao_light_cleanup();
void tt_gfx_ao_light_update_ubo();

tt_ao_light tt_ao_light_new();
void tt_ao_light_delete(tt_ao_light light_id);
void tt_ao_light_set_strength(tt_ao_light light_id, float strength);
void tt_ao_light_set_falloff(tt_ao_light light_id, float falloff);
void tt_ao_light_set_radius(tt_ao_light light_id, float radius);
void tt_ao_light_set_backfacing_attenuation(tt_ao_light light_id, float backfacing_attenuation);
void tt_ao_light_set_bounds(tt_ao_light light_id, tt_vec3 *a, tt_vec3 *b);
int tt_ao_light_get_gpu_index(tt_ao_light light_id);

#endif
