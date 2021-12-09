#version 450

layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec2 base_tex_coord_in;
layout(location = 2) in vec3 normal_in;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 rotation;
uniform mat4 projection;

out vec2 base_tex_coord;

void main()
{
	//basic transformations
	vec4 pos = vec4 (pos_in, 1.0);
	pos = projection * translation * scale * rotation * pos;

	//output
	gl_Position = pos;
	base_tex_coord=base_tex_coord_in;
}