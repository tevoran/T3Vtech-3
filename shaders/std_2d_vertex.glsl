#version 450

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex_coord;

//uniforms
uniform vec2 translation;
uniform vec2 scale;
uniform mat2 rotation;
uniform float aspect;

out vec2 base_tex_coord;

void main()
{
	//transformations
	vec2 pos_tmp = pos * scale;
	pos_tmp = rotation * pos_tmp;
	//pos_tmp.x = pos_tmp.x * aspect;
	pos_tmp = pos_tmp + translation;

	//converting to NDC
	pos_tmp = pos_tmp * 2;
	pos_tmp = pos_tmp - 1;

	//outgoing variables
	gl_Position = vec4(pos_tmp, 1.0, 1.0);
	base_tex_coord=tex_coord;
}