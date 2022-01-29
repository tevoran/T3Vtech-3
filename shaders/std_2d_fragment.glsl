#version 450

//incoming variables
in vec2 base_tex_coord;

//uniforms
uniform sampler2D base_tex;

//outgoing variables
out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord); 
}