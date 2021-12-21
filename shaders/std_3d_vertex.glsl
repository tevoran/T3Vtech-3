#version 450
#define NUM_MAX_DIR_LIGHTS 8
#define NUM_MAX_POINT_LIGHTS 128


layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec2 base_tex_coord_in;
layout(location = 2) in vec3 normal_in;

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

//transformations
uniform mat4 translation;
uniform mat4 scale;
uniform mat4 rotation;
uniform mat4 projection;

//camera
uniform mat4 cam_translation;
uniform mat4 cam_rotation;

//lighting
uniform bool gouraud_shading_toggle;
uniform bool object_light_affected;

//variables to fragment shader
out vec2 base_tex_coord;
out vec4 dir_light_result;
out vec4 point_light_result;

void main()
{
	//basic transformations
	vec4 pos = vec4 (pos_in, 1.0);
	vec4 vertex_world_pos=translation * scale * rotation * pos;
	pos = projection 
		* cam_rotation 
		* cam_translation 
		* vertex_world_pos;
	vec4 normal_tmp = rotation * vec4(normal_in, 1.0);
	vec3 normal=normalize(vec3(normal_tmp.xyz));

	//lighting
	if(object_light_affected)
	{
		//preparation
		point_light_result=vec4(0.0);
		dir_light_result=vec4(0.0);

		//gouraud shading
		if(gouraud_shading_toggle)
		{
			//directional light
			float directional_light_angle[NUM_MAX_DIR_LIGHTS];

			for(int i=0; i<dir_light_num_active.x; i++)
			{
				directional_light_angle[i]=dot(-dir_light_dir[i].xyz, normal);
				if(directional_light_angle[i]<0)
				{
					directional_light_angle[i]=0;
				}
				vec4 tmp_color=vec4(dir_light_color[i].xyz * dir_light_strength[i].xyz, 1.0);
				tmp_color=directional_light_angle[i] * tmp_color;
				dir_light_result += tmp_color;
			}

			//point light
			float point_light_intensity[NUM_MAX_POINT_LIGHTS];

			for(int i=0; i<point_light_num_active.x; i++)
			{
				//getting the direction from the vertex
				vec4 light_direction=point_light_location[i]-vertex_world_pos;

				//determining intensity from light angle
				point_light_intensity[i]=dot(light_direction.xyz, normal);
				if(point_light_intensity[i]<0)
				{
					point_light_intensity[i]=0;
				}

				//taking distance into account
				point_light_intensity[i]=point_light_intensity[i]/
					(length(light_direction.xyz)*length(light_direction.xyz));

				//doing the actual shading
				vec4 tmp_color=vec4(point_light_color[i].xyz * point_light_strength[i].xyz, 1.0);
				tmp_color=point_light_intensity[i] * tmp_color;
				point_light_result+=tmp_color;
			}

		}
	}


	//output
	gl_Position = pos;
	base_tex_coord=base_tex_coord_in;
}