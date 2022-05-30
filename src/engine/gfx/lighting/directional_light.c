#include <tt.h>

/*
Directional light is light that basically is parallel rays from an indefinitely
far away light source. A real life example would be the sun.
It is only active if gouraud shading is active.
*/

#define NUM_MAX_DIR_LIGHTS 8

//using tt_vec4 because of the padding of the uniform buffer object
struct ubo_layout
{
	tt_vec4 num_active;
	tt_vec4 direction[NUM_MAX_DIR_LIGHTS];
	tt_vec4 color[NUM_MAX_DIR_LIGHTS];
	tt_vec4 strength[NUM_MAX_DIR_LIGHTS];
}typedef ubo_layout;


extern GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data

ubo_layout layout;

tt_dir_light dir_light_remap[NUM_MAX_DIR_LIGHTS];

void tt_gfx_directional_light_setup()
{
	glGenBuffers(1, &tt_gfx_ubo_dir_light);
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);

	layout.num_active.x=0;
	layout.num_active.y=0;
	layout.num_active.z=0;
	layout.num_active.w=0;
	for(int i=0; i<NUM_MAX_DIR_LIGHTS; i++)
	{
		layout.direction[i].x=0;
		layout.direction[i].y=0;
		layout.direction[i].z=1;
		layout.direction[i].w=0;
	}
	for(int i=0; i<NUM_MAX_DIR_LIGHTS; i++)
	{
		layout.color[i].x=1; //red
		layout.color[i].y=1; //green
		layout.color[i].z=1; //blue
		layout.color[i].w=0;
	}
	for(int i=0; i<NUM_MAX_DIR_LIGHTS; i++)
	{
		layout.strength[i].x=0.1;
		layout.strength[i].y=0.1;
		layout.strength[i].z=0.1;
		layout.strength[i].w=0.1;
	}
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	for(int i=0; i<NUM_MAX_DIR_LIGHTS; i++)
	{
		dir_light_remap[i]=TT_NO_LIGHT;
	}
}

void tt_gfx_directional_light_cleanup()
{
	glDeleteBuffers(1, &tt_gfx_ubo_dir_light);
}

void tt_gfx_directional_light_update_ubo()
{
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);	
}

//max number of directional lights is currently 8
//the same value can be found in the std_3d_vertex shader
tt_dir_light tt_directional_light_new()
{
	layout.num_active.x++;
	if(layout.num_active.x>NUM_MAX_DIR_LIGHTS)
	{
		layout.num_active.x=NUM_MAX_DIR_LIGHTS;
	}

	tt_dir_light out=TT_NO_LIGHT;
	for(int i=0; i<NUM_MAX_DIR_LIGHTS; i++)
	{
		if(dir_light_remap[i]==TT_NO_LIGHT)
		{
			dir_light_remap[i]=layout.num_active.x;
			out=i;
			break;
		}
	}
	return out;
}

void tt_directional_light_delete(tt_dir_light light_id)
{
	if(light_id==TT_NO_LIGHT)
	{
		return;
	}

	layout.num_active.x--;
	if(layout.num_active.x<=0)
	{
		layout.num_active.x=0;
	}

	int gpu_id=dir_light_remap[light_id]-1;

	//move last entry to the deleted entry
	int i=layout.num_active.x;

	layout.direction[gpu_id].x=layout.direction[i].x;
	layout.direction[gpu_id].y=layout.direction[i].y;
	layout.direction[gpu_id].z=layout.direction[i].z;
	layout.direction[gpu_id].w=layout.direction[i].w;
	layout.color[gpu_id].x=layout.color[i].x;
	layout.color[gpu_id].y=layout.color[i].y;
	layout.color[gpu_id].z=layout.color[i].z;
	layout.strength[gpu_id].x=layout.strength[i].x;
	layout.strength[gpu_id].y=layout.strength[i].y;
	layout.strength[gpu_id].z=layout.strength[i].z;
	layout.strength[gpu_id].w=layout.strength[i].w;

	//delete last entry
	layout.direction[i].x=0;
	layout.direction[i].y=0;
	layout.direction[i].z=1.0;
	layout.direction[i].w=0;	
	layout.color[i].x=1.0;
	layout.color[i].y=1.0;
	layout.color[i].z=1.0;
	layout.strength[i].x=1.0;
	layout.strength[i].y=1.0;
	layout.strength[i].z=1.0;
	layout.strength[i].w=1.0;

	dir_light_remap[i]=dir_light_remap[light_id];
	dir_light_remap[light_id]=TT_NO_LIGHT;
}

void tt_directional_light_set_direction(tt_dir_light light_id, tt_vec3 *direction)
{
	if(light_id==TT_NO_LIGHT)
	{
		return;
	}

	int gpu_id=dir_light_remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	layout.direction[gpu_id].x=direction->x;
	layout.direction[gpu_id].y=direction->y;
	layout.direction[gpu_id].z=direction->z;
}

void tt_directional_light_set_strength(tt_dir_light light_id, float strength)
{
	if(light_id==TT_NO_LIGHT)
	{
		return;
	}

	int gpu_id=dir_light_remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	layout.strength[gpu_id].x=strength;
	layout.strength[gpu_id].y=strength;
	layout.strength[gpu_id].z=strength;
	layout.strength[gpu_id].w=strength;
}

void tt_directional_light_set_color(tt_dir_light light_id, tt_vec3 *color)
{
	if(light_id==TT_NO_LIGHT)
	{
		return;
	}

	int gpu_id=dir_light_remap[light_id];
	if(!gpu_id)
	{
		return;
	}
	gpu_id--;
	layout.color[gpu_id].x=color->x;
	layout.color[gpu_id].y=color->y;
	layout.color[gpu_id].z=color->z;
}