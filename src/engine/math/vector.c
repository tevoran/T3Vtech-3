#include <tt.h>

tt_vec4 tt_math_vec4_normalize(tt_vec4 v)
{
	tt_vec4 v_out;
	float length=sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	v_out.x=v.x/length;
	v_out.y=v.y/length;
	v_out.z=v.z/length;
	v_out.w=v.w/length;
	return v_out;
}