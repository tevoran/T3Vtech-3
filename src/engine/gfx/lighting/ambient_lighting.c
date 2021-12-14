#include <tt.h>

extern float tt_gfx_amb_light_strength; //the ambient light strength
extern tt_vec3 tt_gfx_amb_light_color; //the ambient light color

void tt_ambient_light_set_strength(float strength)
{
	if(strength<0)
	{
		strength=0;
	}
	tt_gfx_amb_light_strength=strength;
}

void tt_ambient_light_set_color(tt_vec3 *color)
{
	tt_gfx_amb_light_color=*color;
}