#ifndef TT_MATH_MATRIX_H
#define TT_MATH_MATRIX_H

//mat2
struct tt_mat2
{
	float array[2][2];
} typedef tt_mat2;

//mat3
struct tt_mat3
{
	float array[3][3];
} typedef tt_mat3;

//mat4
struct tt_mat4
{
	float array[4][4];
} typedef tt_mat4;

//mat2 functions
void tt_math_mat2_make_identity_matrix(tt_mat2 *mat);

//mat3 functions
tt_mat3 tt_math_mat4_crop_to_mat3(tt_mat4 *mat);
tt_vec3 tt_math_mat3_mul_vec3(tt_mat3 *mat, tt_vec3 *vec);

//mat4 functions
void tt_math_mat4_make_identity_matrix(tt_mat4 *mat);
void tt_math_mat4_make_projection_matrix(
	tt_mat4 *mat,
	const uint32_t res_x,
	const uint32_t res_y,
	const float fov,
	const float near_clipping_plane,
	const float far_clipping_plane);
tt_mat4 tt_math_mat4_make_quat_rot_mat(tt_vec3 *rot_axis, float radians);
tt_mat4 tt_math_mat4_mul(tt_mat4 *a, tt_mat4 *b); //a will be multiplied with b
tt_mat4 tt_math_mat4_transpose(tt_mat4 *a);

#endif
