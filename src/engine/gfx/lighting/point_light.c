#include <tt.h>

#define NUM_MAX_POINT_LIGHTS 16

extern GLuint tt_gfx_ubo_point_light; //uniform buffer object for point light data

//using tt_vec4 because of the padding of the uniform buffer object
//warning: the guaranteed size of an UBO is only 16KB
struct ubo_layout
{
	tt_vec4 num_active;
	tt_vec4 location[NUM_MAX_POINT_LIGHTS];
	tt_vec4 color[NUM_MAX_POINT_LIGHTS];
	tt_vec4 strength[NUM_MAX_POINT_LIGHTS];
}typedef ubo_layout;

ubo_layout ubo;

void tt_gfx_point_light_setup()
{
	glGenBuffers(1, &tt_gfx_ubo_point_light);
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);

	//initialization of the memory
	ubo.num_active.x=0;
	for(int i=0; i<NUM_MAX_POINT_LIGHTS; i++)
	{
		ubo.location[i].x=0;
		ubo.location[i].y=0;
		ubo.location[i].z=0;
	}
	for(int i=0; i<NUM_MAX_POINT_LIGHTS; i++)
	{
		ubo.color[i].x=1; //r
		ubo.color[i].y=1; //g
		ubo.color[i].z=1; //b
	}
	for(int i=0; i<NUM_MAX_POINT_LIGHTS; i++)
	{
		ubo.strength[i].x=1.0;
		ubo.strength[i].y=1.0;
		ubo.strength[i].z=1.0;
		ubo.strength[i].w=1.0;
	}
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_gfx_point_light_cleanup()
{
	glDeleteBuffers(1, &tt_gfx_ubo_point_light);
}

int tt_point_light_new(tt_vec3 *position, tt_vec3 *color)
{
	ubo.num_active.x++;
	int i=(int)ubo.num_active.x-1;
	if(ubo.num_active.x>NUM_MAX_POINT_LIGHTS)
	{
		ubo.num_active.x=NUM_MAX_POINT_LIGHTS;
		return 0;
	}
	else
	{

		ubo.location[i].x=position->x;
		ubo.location[i].y=position->y;
		ubo.location[i].z=position->z;

		ubo.color[i].x=color->x;
		ubo.color[i].y=color->y;
		ubo.color[i].z=color->z;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return i;
}