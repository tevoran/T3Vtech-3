#version 450
#define NUM_MAX_DIR_LIGHTS 8


//directional lighting light sources
layout(std140, binding = 0) uniform dir_light
{
	vec4 dir_light_num_active; //active number of lights
	vec4 dir_light_dir[NUM_MAX_DIR_LIGHTS]; //direction
	vec4 dir_light_color[NUM_MAX_DIR_LIGHTS]; //light color
	vec4 dir_light_strength[NUM_MAX_DIR_LIGHTS]; //light intensity
};

in vec2 base_tex_coord;
in float directional_light_angle[NUM_MAX_DIR_LIGHTS];


uniform bool object_light_affected;

uniform sampler2D base_tex;
uniform bool gouraud_shading_toggle;


out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord);

	//lighting
	if(object_light_affected)
	{
		if(gouraud_shading_toggle)
		{
			//directional lighting
			vec4 tmp_color[NUM_MAX_DIR_LIGHTS];
			for(int i=0; i<dir_light_num_active.x; i++)
			{
				tmp_color[i]=vec4(dir_light_color[i].xyz * dir_light_strength[i].xyz, 1.0);
				tmp_color[i]=directional_light_angle[i] * tmp_color[i];
				color += tmp_color[i];
			}
		}		
	}
}