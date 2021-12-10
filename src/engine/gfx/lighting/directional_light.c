#include <tt.h>

/*
Directional light is light that basically is parallel rays from an indefinitely
far away light source. A real life example would be the sun.
It is only active if gouraud shading is active.
*/

extern tt_vec3 tt_gfx_light_direction; //the current direction of the light
extern tt_vec3 tt_gfx_light_direction_color; //the current color of the directional light
extern float tt_gfx_light_direction_strength; //directional light strength


void tt_gfx_set_light_direction(tt_vec3 *direction)
{
	tt_gfx_light_direction=*direction;
}

void tt_gfx_set_light_direction_color(tt_vec3 *color)
{
	tt_gfx_light_direction_color=*color;
}

void tt_gfx_set_light_direction_strength(float strength)
{
	tt_gfx_light_direction_strength=strength;
}