#ifndef TT_MATH_MATRIX_H
#define TT_MATH_MATRIX_H

struct tt_mat4
{
	float array[4][4];
} typedef tt_mat4;


void tt_math_mat4_make_identity_matrix(tt_mat4 *mat);
void tt_math_mat4_make_projection_matrix(
	tt_mat4 *mat,
	const uint32_t res_x,
	const uint32_t res_y,
	const float fov,
	const float near_clipping_plane,
	const float far_clipping_plane);

#endif