#include <tt.h>


extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//3D
//quad
extern GLuint tt_gfx_3d_quad_vao;
extern GLuint tt_gfx_3d_quad_vbo;
extern GLuint tt_gfx_3d_quad_ibo;

//default texture
extern GLuint tt_gfx_3d_default_tex; 


void tt_gfx_quit(const bool quiet)
{
	//delete prepared primitives
	tt_gfx_cleanup_quad();
	tt_gfx_cleanup_cube();


	//delete light UBOs
	tt_gfx_directional_light_cleanup();
	tt_gfx_point_light_cleanup();

	if(!quiet)
	{
		printf("deleting default shaders...");
	}
		glDeleteProgram(tt_std_3d_shader);
		glDeleteProgram(tt_std_2d_shader);
	if(!quiet)
	{
		printf("done\n");
	}

	if(!quiet)
	{
		printf("cleaning up prepared primitives...");
	}
		//quad
		glDeleteVertexArrays(1, &tt_gfx_3d_quad_vao);
		glDeleteBuffers(1, &tt_gfx_3d_quad_vbo);
		glDeleteBuffers(1, &tt_gfx_3d_quad_ibo);

		//default texture
		glDeleteTextures(1, &tt_gfx_3d_default_tex);
	if(!quiet)
	{
		printf("done\n");
	}
}
