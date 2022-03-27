#include <float.h>

float tt_math_f_abs(float value)
{
	return (value<0)
		? -value
		: value;
}

float tt_math_f_min(float a, float b)
{
	return (a<b)
		? a
		: b;
}

float tt_math_f_max(float a, float b)
{
	return (a>b)
		? a
		: b;
}
