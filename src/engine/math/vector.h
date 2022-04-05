#ifndef TT_MATH_VECTOR_H
#define TT_MATH_VECTOR_H

#pragma pack(1)
struct tt_vec2
{
	float x;
	float y;
} typedef tt_vec2;

#pragma pack(1)
struct tt_vec3
{
	float x;
	float y;
	float z;
} typedef tt_vec3;

#pragma pack(1)
struct tt_vec4
{
	float x;
	float y;
	float z;
	float w;
} typedef tt_vec4;

//vec4
tt_vec4 tt_math_vec4_normalize(tt_vec4 *v);

//vec3
float tt_math_vec3_length(tt_vec3 *v);
float tt_math_vec3_length_sq(tt_vec3 *v);
tt_vec3 tt_math_vec3_normalize(tt_vec3 *v);
tt_vec3 tt_math_vec3_rotate(tt_vec3 *rot_axis, float radians, tt_vec3 *vec);
tt_vec3 tt_math_vec3_mul_float(tt_vec3 *v, float a);
tt_vec3 tt_math_vec3_mul(tt_vec3 *a, tt_vec3 *b);
tt_vec3 tt_math_vec3_add(tt_vec3 *a, tt_vec3 *b);
tt_vec3 tt_math_vec3_sub(tt_vec3 *a, tt_vec3 *b);
float tt_math_vec3_dot(tt_vec3 *a, tt_vec3 *b);
tt_vec3 tt_math_vec3_min(tt_vec3 *a, tt_vec3 *b);
tt_vec3 tt_math_vec3_max(tt_vec3 *a, tt_vec3 *b);

#endif
