#version 450
#define NUM_MAX_DIR_LIGHTS 8
#define NUM_MAX_POINT_LIGHTS 128
#define NUM_MAX_POINT_LIGHTS_PER_OBJECT 16


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

uniform vec3 object_color;
uniform vec3 object_emission;

//lighting
uniform bool gouraud_shading_toggle;
uniform bool phong_shading_toggle;

uniform int object_point_light_count;
uniform int object_point_lights[NUM_MAX_POINT_LIGHTS_PER_OBJECT];
uniform bool object_light_affected;

//global settings
uniform bool tone_mapping_toggle;
uniform float exposure;
uniform float saturation;
uniform float contrast;
	
//ambient lighting
uniform float amb_light_strength;
uniform vec3 amb_light_color;

//output
out vec4 color;

vec3 aces_approx(vec3 v)
{
    v *= 0.6f;
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((v * ( a * v + b)) / ( v * (c * v + d) + e), 0.0f, 1.0f);
}

vec3 hable_filmic(vec3 v)
{
    const float A = 0.15;
	const float B = 0.50;
	const float C = 0.10;
	const float D = 0.20;
	const float E = 0.02;
	const float F = 0.30;

	vec3 A_v = A * v;
	vec3 s0 = A_v + C * B;
	vec3 s1 = v * s0 + D * E;
	vec3 s2 = A_v + B;
	vec3 s3 = v * s2 + D * F;

	return s1 / s3 - E / F;
}


float srgb_to_linear(float u)
{
	const float min_srgb_power = 0.04045;

    if (u < min_srgb_power)
	{
        return u / 12.92;
    }
    else
	{
        return pow((u + 0.055) / 1.055, 2.4);
    }
}

vec3 srgb_to_linear(vec3 v)
{
	return vec3(
		srgb_to_linear(v.r),
		srgb_to_linear(v.g),
		srgb_to_linear(v.b)
	);
}

float linear_to_srgb(float u)
{
	const float min_srgb_power = 0.0031308;

	if (u < min_srgb_power)
	{
		return 12.92 * u;
	}
	else
	{
		return 1.055 * pow(u, 1 / 2.4) - 0.055;
	}
}

vec3 linear_to_srgb(vec3 v)
{
	return vec3(
		linear_to_srgb(v.r),
		linear_to_srgb(v.g),
		linear_to_srgb(v.b)
	);	
}

float luminance(vec3 v)
{
	return v.r * 0.2126 + v.g * 0.7152 + v.b * 0.0722;
}

vec3 adjust_contrast(vec3 v, float contrast)
{
	return ((v - 0.5) * max(contrast, 0.0)) + 0.5;
}

void main()
{
	color = vec4(srgb_to_linear(texture(base_tex, base_tex_coord).rgb), 1.0);
	//color = texture(base_tex, base_tex_coord);

	//lighting
	if(object_light_affected)
	{
		//preparation
		vec4 base_color=color;
		base_color.rgb *= srgb_to_linear(object_color);

		//ambient lighting
		vec3 amb_light = amb_light_strength * amb_light_color;
		color = vec4(amb_light, 1.0) * color;

		if(phong_shading_toggle)
		{
			vec3 normal = normalize(normal_out);
			for(int i = 0; i < object_point_light_count; i++)
			{
				int l = object_point_lights[i];

				//getting the direction from the fragment
				vec3 light_direction = point_light_location[l].xyz - world_position_out;

				//determining intensity from light angle
				float l_dot_n = dot(light_direction, normal);
				if(l_dot_n > 0)
				{
					float l_distance = length(light_direction);
					l_dot_n /= l_distance;

					float falloff = 1 / (l_distance * l_distance);
					vec3 diffuse = point_light_color[l].rgb * base_color.rgb * point_light_strength[l].rgb * l_dot_n * falloff;

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

		color.rgb += base_color.rgb * srgb_to_linear(object_emission);
	}

	color.rgb *= exposure;

	float Y = luminance(color.rgb);
	color.rgb = mix(vec3(Y, Y, Y), color.rgb, saturation);

	if (tone_mapping_toggle && object_light_affected)
	{
		color = vec4(hable_filmic(color.rgb), color.a);
	}

	color.rgb = linear_to_srgb(color.rgb);
	color.rgb = adjust_contrast(color.rgb, contrast);
}
