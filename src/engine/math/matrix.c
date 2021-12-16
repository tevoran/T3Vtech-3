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

tt_mat4 tt_math_mat4_make_quat_rot_mat(tt_vec3 *rot_axis, float radians)
{
	tt_vec4 q;
	q.x=rot_axis->x * sin(radians/2);
	q.y=rot_axis->y * sin(radians/2);
	q.z=rot_axis->z * sin(radians/2);
	q.w=cos(radians/2);
	q=tt_math_vec4_normalize(q);

	//the rotation matrix with the difference to the current rotation matrix
	tt_mat4 rot_mat;
	rot_mat.array[0][0]=1-2*(q.y*q.y+q.z*q.z);
	rot_mat.array[0][1]=2*(q.x*q.y+q.z*q.w);
	rot_mat.array[0][2]=2*(q.x*q.z-q.y*q.w);
	rot_mat.array[0][3]=0;

	rot_mat.array[1][0]=2*(q.x*q.y-q.w*q.z);
	rot_mat.array[1][1]=1-2*(q.x*q.x+q.z*q.z);
	rot_mat.array[1][2]=2*(q.y*q.z+q.x*q.w);
	rot_mat.array[1][3]=0;

	rot_mat.array[2][0]=2*(q.x*q.z+q.y*q.w);
	rot_mat.array[2][1]=2*(q.y*q.z-q.x*q.w);
	rot_mat.array[2][2]=1-2*(q.x*q.x+q.y*q.y);
	rot_mat.array[2][3]=0;

	rot_mat.array[3][0]=0;
	rot_mat.array[3][1]=0;
	rot_mat.array[3][2]=0;
	rot_mat.array[3][3]=1;

	return rot_mat;
}

tt_mat4 tt_math_mat4_mul(tt_mat4 *a, tt_mat4 *b)
{
	tt_mat4 out;
	for(int iy=0; iy<4; iy++)
	{
		for(int ix=0; ix<4; ix++)
		{
			out.array[iy][ix]=
				a->array[iy][0] * b->array[0][ix]
				+ a->array[iy][1] * b->array[1][ix]
				+ a->array[iy][2] * b->array[2][ix]
				+ a->array[iy][3] * b->array[3][ix];
		}
	}
	return out;
}