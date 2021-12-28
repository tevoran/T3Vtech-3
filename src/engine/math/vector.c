#include <tt.h>

tt_vec4 tt_math_vec4_normalize(tt_vec4 v)
{
	tt_vec4 v_out;
	float length=sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	v_out.x=v.x/length;
	v_out.y=v.y/length;
	v_out.z=v.z/length;
	v_out.w=v.w/length;
	return v_out;
}

float tt_math_vec3_length(tt_vec3 v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

tt_vec3 tt_math_vec3_rotate(tt_vec3 *rot_axis, float radians, tt_vec3 *vec)
{
	tt_mat4 tmp_rot_mat=tt_math_mat4_make_quat_rot_mat(rot_axis, radians);
	tt_mat4 tmp_mat;
	tt_math_mat4_make_identity_matrix(&tmp_mat);
	tmp_mat.array[3][0]=vec->x;
	tmp_mat.array[3][1]=vec->y;
	tmp_mat.array[3][2]=vec->z;


	tmp_mat=tt_math_mat4_mul(&tmp_mat, &tmp_rot_mat);
	tt_vec3 out_vec;
	out_vec.x=tmp_mat.array[3][0];
	out_vec.y=tmp_mat.array[3][1];
	out_vec.z=tmp_mat.array[3][2];
	return out_vec;
}

tt_vec3 tt_math_vec3_add(tt_vec3 *a, tt_vec3 *b)
{
	tt_vec3 out;
	out.x=a->x + b->x;
	out.y=a->y + b->y;
	out.z=a->z + b->z;
	return out;
}