#version 450

layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec2 base_tex_coord_in;
layout(location = 2) in vec3 normal_in;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 rotation;
uniform mat4 projection;

uniform bool gouraud_shading_toggle;

out vec2 base_tex_coord;
out float gouraud_strength;

void main()
{
	//basic transformations
	vec4 pos = vec4 (pos_in, 1.0);
	pos = projection * translation * scale * rotation * pos;
	vec4 normal_tmp = rotation * vec4(normal_in, 1.0);
	vec3 normal=normalize(vec3(normal_tmp.xyz));

	//gouraud shading
	vec3 light_dir=vec3(-1.0, 0.0, 0.0);
	if(gouraud_shading_toggle)
	{
		gouraud_strength=dot(-light_dir, normal);
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