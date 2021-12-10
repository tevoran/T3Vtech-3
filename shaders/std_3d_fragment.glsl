#version 450

in vec2 base_tex_coord;
in float gouraud_strength;
in vec3 directional_light_color;
in float directional_light_strength;

uniform sampler2D base_tex;

out vec4 color;

void main()
{
	color = texture(base_tex, base_tex_coord);

	//lighting
	vec4 directional_light = vec4( directional_light_color * directional_light_strength , 1.0);
	color = gouraud_strength * (directional_light + color);
}