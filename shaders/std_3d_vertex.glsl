#version 450

layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec2 base_tex_coord_in;
layout(location = 2) in vec3 normal_in;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 rotation;
uniform mat4 projection;

//gouraud shading
uniform bool gouraud_shading_toggle;
uniform vec3 gouraud_shading_dir;
uniform vec3 gouraud_shading_color;
uniform float gouraud_shading_light_strength;

out vec2 base_tex_coord;
out float gouraud_strength;
out vec3 directional_light_color;
out float directional_light_strength;

void main()
{
	//basic transformations
	vec4 pos = vec4 (pos_in, 1.0);
	pos = projection * translation * scale * rotation * pos;
	vec4 normal_tmp = rotation * vec4(normal_in, 1.0);
	vec3 normal=normalize(vec3(normal_tmp.xyz));

	//gouraud shading
	directional_light_color=gouraud_shading_color;
	directional_light_strength=gouraud_shading_light_strength;
	if(gouraud_shading_toggle)
	{
		gouraud_strength=dot(-gouraud_shading_dir, normal);
		if(gouraud_strength<0)
		{
			gouraud_strength=0;
		}
	}
	else
	{
		gouraud_strength=1;
	}

	//output
	gl_Position = pos;
	base_tex_coord=base_tex_coord_in;
}