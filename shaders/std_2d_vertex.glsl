#version 450

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex_coord;

//uniforms
uniform vec2 translation;

out vec2 base_tex_coord;

void main()
{
	vec2 pos_tmp = pos + translation;

	//outgoing variables
	gl_Position = vec4(pos_tmp, 1.0, 1.0);
	base_tex_coord=tex_coord;
}