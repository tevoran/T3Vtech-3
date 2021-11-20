#include <tt.h>

extern GLuint tt_std_3d_shader; //the default shader for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader for all 2d objects

//returns true if successfull
bool tt_gfx_init()
{
	//creating the standard shaders
	tt_std_2d_shader=tt_gfx_create_shader(
		NULL,
		"shaders/std_2d_vertex.glsl",
		NULL,
		NULL,
		NULL,
		"shaders/std_fragment.glsl");
	if(tt_std_2d_shader==0)
	{
		printf("[ERROR] failed to create the standard 2d shader\n");
		return false;
	}
	else
	{
		printf("successfully built the standard 2d shader\n");
	}

	tt_std_3d_shader=tt_gfx_create_shader(
		NULL,
		"shaders/std_3d_vertex.glsl",
		NULL,
		NULL,
		NULL,
		"shaders/std_fragment.glsl");
	if(tt_std_3d_shader==0)
	{
		printf("[ERROR] failed to create the standard 2d shader\n");
		return false;
	}
	else
	{
		printf("successfully built the standard 2d shader\n");
	}
	
	return true;
}