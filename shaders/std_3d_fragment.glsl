#version 450
#define NUM_MAX_DIR_LIGHTS 8
#define NUM_MAX_POINT_LIGHTS 128


//directional lighting light sources
//vec4 is used because of the padding of the UBO
layout(std140, binding = 0) uniform dir_light
{
	vec4 dir_light_num_active; //active number of lights
	vec4 dir_light_dir[NUM_MAX_DIR_LIGHTS]; //direction
	vec4 dir_light_color[NUM_MAX_DIR_LIGHTS]; //light color
	vec4 dir_light_strength[NUM_MAX_DIR_LIGHTS]; //light intensity
};

//point light sources
//vec4 is used because of the padding of the UBO
layout(std140, binding = 1) uniform point_light
{
	vec4 point_light_num_active; //active number of lights
	vec4 point_light_location[NUM_MAX_POINT_LIGHTS]; //where is the point light
	vec4 point_light_color[NUM_MAX_POINT_LIGHTS]; //light color
	vec4 point_light_strength[NUM_MAX_POINT_LIGHTS]; //light intensity
};

//input from the vertex shader
in vec2 base_tex_coord;
in vec4 dir_light_result;
in vec4 point_light_result;
in vec3 normal_out;
in vec3 world_position_out;

uniform sampler2D base_tex;

//lighting
uniform bool gouraud_shading_toggle;
uniform bool phong_shading_toggle;
uniform bool object_light_affected;
	
//ambient lighting
uniform float amb_light_strength;
uniform vec3 amb_light_color;

//output
out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord);

	//lighting
	if(object_light_affected)
	{
		//preparation
		vec4 base_color=color;

		//ambient lighting
		vec3 amb_light = amb_light_strength * amb_light_color;
		color = vec4(amb_light, 1.0) * color;

		if(phong_shading_toggle)
		{
			for(int i = 0; i < point_light_num_active.x; i++)
			{
				//getting the direction from the fragment
				vec3 light_direction = point_light_location[i].xyz - world_position_out;

				//determining intensity from light angle
				float l_dot_n = dot(light_direction, normal_out);
				if(l_dot_n > 0)
				{
					float l_distance = length(light_direction);
					l_dot_n /= l_distance;

					float falloff = 1 / (l_distance * l_distance);
					vec3 diffuse = base_color.rgb * point_light_strength[i].rgb * l_dot_n * falloff;

					color += vec4(diffuse, 0.0);
				}
			}
		}

		//gouraud shading based lighting
		if(gouraud_shading_toggle)
		{
			//directional lighting
//			vec4 tmp_color;
//			for(int i=0; i<dir_light_num_active.x; i++)
//			{
//				tmp_color=vec4(dir_light_color[i].xyz * dir_light_strength[i].xyz, 1.0);
//				tmp_color=directional_light_angle[i] * tmp_color;
//				color += tmp_color;
//			}
			color+=base_color * dir_light_result;
		
			//point lights
			color+=base_color * point_light_result;

		}		
	}
}