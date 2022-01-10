#include <tt.h>

float tt_math_f_abs(float value)
{
	if(value<0)
	{
		value*=-1;
	}
	return value;
}
