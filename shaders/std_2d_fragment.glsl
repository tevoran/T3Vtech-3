#version 430

//incoming variables
in vec2 base_tex_coord;

//uniforms
uniform sampler2D base_tex;
uniform float transparency;

//outgoing variables
out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord);
	color.a = color.a * transparency;
}