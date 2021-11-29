#include <tt.h>

//this is the beginning of the 3D object rendering list
extern tt_node *tt_3d_list_entry_node;

tt_3d_object* tt_3d_object_new() 
{
	//creating the 3d object and putting it into the render list
	tt_3d_object *new_object=malloc(sizeof(tt_3d_object));
	new_object->node=tt_list_new_node(tt_3d_list_entry_node);
	if(!tt_3d_list_entry_node) //save the entry node if it's one
	{
		tt_3d_list_entry_node=new_object->node;
	}
	tt_list_node_set_data(new_object->node, new_object);

	//initializing the object to default values
	new_object->num_verts=0;
	new_object->vao=0;
	new_object->vbo=0;
	new_object->ibo=0;

	tt_math_mat4_make_identity_matrix(&new_object->translation);
	tt_math_mat4_make_identity_matrix(&new_object->scale);
	tt_math_mat4_make_identity_matrix(&new_object->rotation);

	return new_object;
}

//the function uses a pointer pointer so that the deleted object pointer can
//be set to NULL. This is done to reduce possible segfaults by accidentally
//deleting the same object twice.
void tt_3d_object_delete(tt_3d_object **object)
{
	//if this object has already been deleted then just quit
	if(*object==NULL)
	{
		return; 
	}

	//if this object is the first object in the render list
	if((*object)->node==tt_3d_list_entry_node)
	{
		tt_list_remove_node(&tt_3d_list_entry_node);
	}
	else
	{
		tt_list_remove_node(&(*object)->node);
	}

	free(*object);
	*object=NULL; //mark object as deleted
}

//transformations
void tt_3d_object_scale(tt_3d_object *object, tt_vec3 *scale)
{
	object->scale.array[0][0]=scale->x;
	object->scale.array[1][1]=scale->y;
	object->scale.array[2][2]=scale->z;
}

void tt_3d_object_set_position(tt_3d_object *object, tt_vec3 *position)
{
	object->translation.array[3][0]=position->x;
	object->translation.array[3][1]=position->y;
	object->translation.array[3][2]=position->z;
}

void tt_3d_object_rotate(tt_3d_object *object, tt_vec3 *rot_axis, float radians)
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

	object->rotation=tt_math_mat4_mul(&rot_mat, &object->rotation);
}

/*
void gfx_model_rotate(struct model *model, float rotation, struct vec3f rot_axis)
{
	calculating quaternions
	struct vec4f q;
		q.x=rot_axis.x*sin(rotation/2);
		q.y=rot_axis.y*sin(rotation/2);
		q.z=rot_axis.z*sin(rotation/2);
		q.w=cos(rotation/2);

	q=normalize4f(q);
	
	GLfloat current_rotation_matrix[4][4]=
	{
		1-2*(q.y*q.y+q.z*q.z), 2*(q.x*q.y+q.z*q.w), 2*(q.x*q.z-q.y*q.w), 0,
		2*(q.x*q.y-q.w*q.z), 1-2*(q.x*q.x+q.z*q.z), 2*(q.y*q.z+q.x*q.w), 0,
		2*(q.x*q.z+q.y*q.w), 2*(q.y*q.z-q.x*q.w), 1-2*(q.x*q.x+q.y*q.y), 0,
		0, 0, 0, 1
	};
	
	float new_rotation_matrix[4][4];
	
	calculating the new rotation matrix that is sent to the shader
	matrix_multiplication4x4(current_rotation_matrix, model->rotation_matrix, new_rotation_matrix);

	
	saving the rotation matrix in the model struct for the new_frame command
	 * to put it into the shader
	for(int ix=0,iy=0; iy<4; ix++)
	{
		model->rotation_matrix[ix][iy]=new_rotation_matrix[ix][iy];
		if(ix==3)
		{
			ix=-1;
			iy++;
		}
	}
}
*/