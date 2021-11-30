#version 450

in vec2 base_tex_coord;

uniform sampler2D base_tex;

out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord);
	//color = vec4(1.0, 0.6, 0.2, 1.0); 
}