#ifndef TT_MATH_VECTOR_H
#define TT_MATH_VECTOR_H

struct tt_vec3
{
	float x;
	float y;
	float z;
} typedef tt_vec3;

struct tt_vec4
{
	float x;
	float y;
	float z;
	float w;
} typedef tt_vec4;

tt_vec4 tt_math_vec4_normalize(tt_vec4 v);

#endif