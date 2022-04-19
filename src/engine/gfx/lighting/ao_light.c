#include <tt.h>

#define NUM_MAX_AO_LIGHTS 128

extern GLuint tt_gfx_ubo_ao_light; //uniform buffer object for ao light data

struct ao_light_data
{
	tt_vec4 p0;
	tt_vec4 p1;
} typedef ao_light_data;

struct ao_light_ubo_layout
{
	ao_light_data ao_lights[NUM_MAX_AO_LIGHTS];
} typedef ao_light_ubo_layout;

ao_light_ubo_layout ubo;


//light source remapping array
tt_ao_light remap[NUM_MAX_AO_LIGHTS];
int n_active_ao_lights = 0;


void tt_gfx_ao_light_setup()
{
	glGenBuffers(1, &tt_gfx_ubo_ao_light);
	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	for(int i=0; i< NUM_MAX_AO_LIGHTS; i++)
	{
		remap[i]=TT_NO_LIGHT;
	}
}

void tt_gfx_ao_light_cleanup()
{
	glDeleteBuffers(1, &tt_gfx_ubo_ao_light);
}

tt_ao_light tt_ao_light_new()
{
	if(n_active_ao_lights>=NUM_MAX_AO_LIGHTS)
	{
		n_active_ao_lights=NUM_MAX_AO_LIGHTS;
		return TT_NO_LIGHT;
	}

	++n_active_ao_lights;

	tt_ao_light out=TT_NO_LIGHT;
	for(int i=0; i<NUM_MAX_AO_LIGHTS; i++)
	{
		if(remap[i]==TT_NO_LIGHT)
		{
			remap[i]=n_active_ao_lights;
			out=(tt_ao_light)i;
			break;
		}
	}

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return out;

}

void tt_ao_light_delete(tt_ao_light light_id)
{
	if(light_id==TT_NO_LIGHT || n_active_ao_lights==0)
	{
		return;
	}

	int gpu_id=remap[light_id]-1;

	//move last entry to the deleted entry
	ubo.ao_lights[gpu_id]=ubo.ao_lights[n_active_ao_lights - 1];
	--n_active_ao_lights;

	for (int j = 0; j < NUM_MAX_AO_LIGHTS; ++j)
	{
		if (remap[j]==n_active_ao_lights + 1)
		{
			remap[j] = gpu_id + 1;
		}
	}

	remap[light_id]=TT_NO_LIGHT;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_ao_light_set_strength(tt_ao_light light_id, float strength)
{
	if(light_id==TT_NO_LIGHT)
	{
		return; 
	}

	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}

	if (strength < 0)
	{
		strength = 0;
	}
	else if (strength >= 1)
	{
		strength = 0.9999f;
	}

	float prev_strength_falloff=ubo.ao_lights[gpu_id - 1].p0.w;
	float prev_falloff=floor(prev_strength_falloff);

	ubo.ao_lights[gpu_id - 1].p0.w = prev_falloff + strength;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_ao_light_set_falloff(tt_ao_light light_id, float falloff)
{
	if(light_id==TT_NO_LIGHT)
	{
		return; 
	}

	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}

	if (falloff < 0)
	{
		falloff = 0;
	}

	float prev_strength_falloff=ubo.ao_lights[gpu_id - 1].p0.w;
	float prev_strength=prev_strength_falloff - floor(prev_strength_falloff);

	ubo.ao_lights[gpu_id - 1].p0.w = falloff * 100.0f + prev_strength;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_ao_light_set_radius(tt_ao_light light_id, float radius)
{
	if(light_id==TT_NO_LIGHT)
	{
		return; 
	}

	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}

	if (radius < 0)
	{
		radius = 0;
	}

	ubo.ao_lights[gpu_id-1].p1.w = radius;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void tt_ao_light_set_bounds(tt_ao_light light_id, tt_vec3 *a, tt_vec3 *b)
{
	if(light_id==TT_NO_LIGHT)
	{
		return; 
	}

	int gpu_id=remap[light_id];
	if(!gpu_id)
	{
		return;
	}

	ubo.ao_lights[gpu_id-1].p0.x = a->x;
	ubo.ao_lights[gpu_id-1].p0.y = a->y;
	ubo.ao_lights[gpu_id-1].p0.z = a->z;

	ubo.ao_lights[gpu_id-1].p1.x = b->x;
	ubo.ao_lights[gpu_id-1].p1.y = b->y;
	ubo.ao_lights[gpu_id-1].p1.z = b->z;

	glBindBuffer(GL_UNIFORM_BUFFER, tt_gfx_ubo_ao_light);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ao_light_ubo_layout), &ubo, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
