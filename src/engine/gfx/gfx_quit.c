#include <tt.h>


extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//3D
//quad
extern GLuint tt_gfx_3d_quad_vao;
extern GLuint tt_gfx_3d_quad_vbo;
extern GLuint tt_gfx_3d_quad_ibo;

void tt_gfx_quit()
{
	printf("deleting default shaders...");
		glDeleteProgram(tt_std_3d_shader);
		glDeleteProgram(tt_std_2d_shader);
	printf("done\n");

	printf("cleaning up prepared primitives...");
		glDeleteVertexArrays(1, &tt_gfx_3d_quad_vao);
		glDeleteBuffers(1, &tt_gfx_3d_quad_vbo);
		glDeleteBuffers(1, &tt_gfx_3d_quad_ibo);
	printf("done\n");
}
