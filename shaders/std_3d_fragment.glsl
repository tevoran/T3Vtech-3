#version 450
#define NUM_MAX_DIR_LIGHTS 8
#define NUM_MAX_POINT_LIGHTS 128
#define NUM_MAX_POINT_LIGHTS_PER_OBJECT 16
#define NUM_MAX_AO_LIGHTS 256
#define NUM_MAX_AO_LIGHTS_PER_OBJECT 16

struct ao_light
{
	vec4 p0;
	vec4 p1;
	float strength;
	float falloff;
	float radius;
	float backfacing_attenuation;
};

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

layout(std140, binding = 2) uniform ao_lights_buffer
{
	ao_light ao_lights[NUM_MAX_AO_LIGHTS];
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
uniform int object_ao_light_count;
uniform int object_ao_lights[NUM_MAX_AO_LIGHTS_PER_OBJECT];
uniform bool object_light_affected;

//global settings
uniform bool tone_mapping_toggle;
uniform float exposure;
uniform float saturation;
uniform float contrast;
	
//ambient lighting
uniform float amb_light_strength;
uniform vec3 amb_light_color;

//fog
uniform bool fog_active;
uniform vec3 fog_color;
uniform float fog_max_distance;
uniform float fog_min_distance;

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

float get_ao(vec3 pos, vec3 normal, in ao_light light)
{
	float strength = light.strength;
	float falloff = light.falloff;
	float radius = light.radius;
	float backfacing_attenuation = light.backfacing_attenuation;

	vec3 closest_point = vec3(
		clamp(pos.x, light.p0.x, light.p1.x),
		clamp(pos.y, light.p0.y, light.p1.y),
		clamp(pos.z, light.p0.z, light.p1.z)
	);

	vec3 center = 0.5 * (light.p0.xyz + light.p1.xyz);
	float distance = max(length(pos - closest_point) - radius, 0);
	float normal_dot_delta = backfacing_attenuation * max(0.0, sign(-dot(normal, pos - center))) + (1 - backfacing_attenuation);

	return exp(-distance * falloff) * strength * normal_dot_delta;
}

void main()
{
	color = vec4(srgb_to_linear(texture(base_tex, base_tex_coord).rgb), 1.0);

	//lighting
	if(object_light_affected)
	{
		//preparation
		vec4 base_color=color;
		base_color.rgb *= srgb_to_linear(object_color);

		vec3 normal = normalize(normal_out);

		//calculate ambient occlusion
		float ao = 0.0;
		for (int i = 0; i < object_ao_light_count; i++)
		{
			ao = 1 - (1 - ao) * (1 - get_ao(world_position_out, normal, ao_lights[object_ao_lights[i]]));
		}

		//ambient lighting
		vec3 amb_light = amb_light_strength * amb_light_color * (1 - ao);
		color = vec4(amb_light, 1.0) * color;

		if(phong_shading_toggle)
		{
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
					vec3 diffuse = point_light_color[l].rgb * base_color.rgb * point_light_strength[l].rgb * l_dot_n * falloff  * (1 - ao);

					color += vec4(diffuse, 0.0);
				}
			}
		}

		//gouraud shading based lighting
		if(gouraud_shading_toggle)
		{
			//directional lighting
			color+=base_color * dir_light_result;
		
			//point lights
			color+=base_color * point_light_result;
		}

		color.rgb += base_color.rgb * srgb_to_linear(object_emission);
	}

	//fog
	if (fog_active)
	{
		float fog_intensity = 1.0f - (fog_max_distance - gl_FragCoord.z) / (fog_max_distance - fog_min_distance);
		fog_intensity = clamp(fog_intensity, 0.0f, 1.0f);
		color.rgb = fog_intensity * fog_color + (1.0f - fog_intensity) * color.rgb;
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
