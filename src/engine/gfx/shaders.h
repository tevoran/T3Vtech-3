#ifndef TT_GFX_SHADERS_H
#define TT_GFX_SHADERS_H

#include <tt.h>

//not used shaders can be passed as NULL
//although vertex and fragment shaders are necessary to show something
//returns 0 if an error occured
GLuint tt_gfx_create_shader(
	const char *path_to_compute_shader,
	const char *path_to_vertex_shader,
	const char *path_to_tess_control_shader,
	const char *path_to_tess_evaluation_shader,
	const char *path_to_geometry_shader,
	const char *path_to_fragment_shader);

#endif