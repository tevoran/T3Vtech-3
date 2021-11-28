#include <tt.h>

float id_mat4[4][4]={
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0,
};

void tt_math_mat4_make_identity_matrix(tt_mat4 *mat)
{
	for(int iy=0; iy<4; iy++)
	{
		for(int ix=0; ix<4; ix++)
		{
			mat->array[iy][ix]=id_mat4[iy][ix];
		}
	}

}