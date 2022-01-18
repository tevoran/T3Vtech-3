#include <tt.h>

#define NUM_MAX_POINT_LIGHTS 128

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


//light source remapping array
tt_point_light remap[NUM_MAX_POINT_LIGHTS];

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

	for(int i=0; i<NUM_MAX_POINT_LIGHTS; i++)
	{
		remap[i]=NO_LIGHT;
	}
}

void tt_gfx_point_light_cleanup()
{
	glDeleteBuffers(1, &tt_gfx_ubo_point_light);
}

tt_point_light tt_point_light_new()
{
	ubo.num_active.x++;
	if(ubo.num_active.x>NUM_MAX_POINT_LIGHTS)
	{
		ubo.num_active.x=NUM_MAX_POINT_LIGHTS;
		return 0;
	}

	int out=NO_LIGHT;
	for(int i=0; i<NUM_MAX_POINT_LIGHTS; i++)
	{
			printf("remap[%i]= %i\n", i, remap[i]);

		if(remap[i]==NO_LIGHT)
		{
			remap[i]=ubo.num_active.x;
			printf("remap[%i]= %i\n", i, remap[i]);
			out=i;
			break;
		}
	}

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return out;

}

void tt_point_light_delete(tt_point_light light_id)
{
	ubo.num_active.x--;
	if(ubo.num_active.x<0)
	{
		ubo.num_active.x=0;
		return ;
	}

	int gpu_id=remap[light_id]-1;

	//move last entry to the deleted entry
	int i=ubo.num_active.x;
	ubo.location[gpu_id].x=ubo.location[i].x;
	ubo.location[gpu_id].y=ubo.location[i].y;
	ubo.location[gpu_id].z=ubo.location[i].z;
	ubo.color[gpu_id].x=ubo.color[i].x;
	ubo.color[gpu_id].y=ubo.color[i].y;
	ubo.color[gpu_id].z=ubo.color[i].z;
	ubo.strength[gpu_id].x=ubo.strength[i].x;
	ubo.strength[gpu_id].y=ubo.strength[i].y;
	ubo.strength[gpu_id].z=ubo.strength[i].z;
	ubo.strength[gpu_id].w=ubo.strength[i].w;

	//delete last entry
	ubo.location[i].x=0;
	ubo.location[i].y=0;
	ubo.location[i].z=0;
	ubo.color[i].x=1.0;
	ubo.color[i].y=1.0;
	ubo.color[i].z=1.0;
	ubo.strength[i].x=1.0;
	ubo.strength[i].y=1.0;
	ubo.strength[i].z=1.0;
	ubo.strength[i].w=1.0;

	remap[i]=remap[light_id];
	remap[light_id]=NO_LIGHT;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void tt_point_light_set_strength(tt_point_light light_id, float strength)
{
	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	ubo.strength[gpu_id].x=strength;
	ubo.strength[gpu_id].y=strength;
	ubo.strength[gpu_id].z=strength;
	ubo.strength[gpu_id].w=strength;
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_point_light_set_color(tt_point_light light_id, tt_vec3 *color)
{
	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	ubo.color[gpu_id].x=color->x; //r
	ubo.color[gpu_id].y=color->y; //g
	ubo.color[gpu_id].z=color->z; //b
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_point_light_set_position(tt_point_light light_id, tt_vec3 *position)
{
	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	ubo.location[gpu_id].x=position->x;
	ubo.location[gpu_id].y=position->y;
	ubo.location[gpu_id].z=position->z;
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_point_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}