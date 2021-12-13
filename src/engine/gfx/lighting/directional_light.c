#include <tt.h>

/*
Directional light is light that basically is parallel rays from an indefinitely
far away light source. A real life example would be the sun.
It is only active if gouraud shading is active.
*/

#define NUM_MAX_DIR_LIGHTS 8

//usinng tt_vec4 because of the padding of the uniform buffer object
struct ubo_layout
{
	tt_vec4 num_active;
	tt_vec4 direction[NUM_MAX_DIR_LIGHTS];
	tt_vec4 color[NUM_MAX_DIR_LIGHTS];
	tt_vec4 strength[NUM_MAX_DIR_LIGHTS];
}typedef ubo_layout;

extern tt_vec3 tt_gfx_light_direction; //the current direction of the light
extern tt_vec3 tt_gfx_light_direction_color; //the current color of the directional light
extern float tt_gfx_light_direction_strength; //directional light strength

extern GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data

ubo_layout layout;

void tt_gfx_directional_light_setup()
{
	glGenBuffers(1, &tt_gfx_ubo_dir_light);
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);

	//allocating 72 bytes which is the data occupied by the 8 possible light sources
	//more information can be found in the std_3d_vertex shader
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
		layout.direction[i].w=0;
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
}

void tt_gfx_directional_light_cleanup()
{
	glDeleteBuffers(1, &tt_gfx_ubo_dir_light);
}

//max number of directional lights is currently 8
//the same value can be found in the std_3d_vertex shader
int tt_directional_light_new()
{
	layout.num_active.x++;
	if(layout.num_active.x>NUM_MAX_DIR_LIGHTS)
	{
		layout.num_active.x=NUM_MAX_DIR_LIGHTS;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);	
	return layout.num_active.x;
}

void tt_directional_light_destroy(int light_id)
{
	layout.num_active.x=light_id-1;
	if(layout.num_active.x<=0)
	{
		layout.num_active.x=0;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_directional_light_set_direction(int light_id, tt_vec3 *direction)
{
	layout.direction[light_id-1].x=direction->x;
	layout.direction[light_id-1].y=direction->y;
	layout.direction[light_id-1].z=direction->z;
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_directional_light_set_strength(int light_id, float strength)
{
	layout.strength[light_id-1].x=strength;
	layout.strength[light_id-1].y=strength;
	layout.strength[light_id-1].z=strength;
	layout.strength[light_id-1].w=strength;
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_directional_light_set_color(int light_id, tt_vec3 *color)
{
	layout.color[light_id-1].x=color->x;
	layout.color[light_id-1].y=color->y;
	layout.color[light_id-1].z=color->z;
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_dir_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(layout), &layout, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}