#ifndef TT_MATH_MATRIX_H
#define TT_MATH_MATRIX_H

struct tt_mat4
{
	float array[4][4];
} typedef tt_mat4;


void tt_math_mat4_make_identity_matrix(tt_mat4 *mat);

#endif