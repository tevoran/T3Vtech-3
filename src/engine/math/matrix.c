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

void tt_math_mat4_make_projection_matrix(
	tt_mat4 *mat,
	const uint32_t res_x,
	const uint32_t res_y,
	const float fov,
	const float near_clipping_plane,
	const float far_clipping_plane)
{
	float aspect=(float)res_x/res_y;
	mat->array[0][0]=tan(0.5*tt_PI-0.5*fov);
	mat->array[0][1]=0;
	mat->array[0][2]=0;
	mat->array[0][3]=0;

	mat->array[1][0]=0;
	mat->array[1][1]=aspect*tan(0.5*tt_PI-0.5*fov);
	mat->array[1][2]=0;
	mat->array[1][3]=0;

	mat->array[2][0]=0;
	mat->array[2][1]=0;
	mat->array[2][2]=0;
	mat->array[2][3]=1;

	mat->array[3][0]=0;
	mat->array[3][1]=0;
	mat->array[3][2]=
		-(1 - near_clipping_plane) / (far_clipping_plane - near_clipping_plane);
	mat->array[3][3]=0;
}