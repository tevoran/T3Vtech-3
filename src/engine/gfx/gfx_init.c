#include <tt.h>

extern uint32_t tt_res_x; //game resolution
extern uint32_t tt_res_y; //game resolution
extern float tt_near_plane; //near clipping plane
extern float tt_far_plane; //far clipping plane
extern float tt_fov; //field of view in radians
extern tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix
extern GLuint tt_std_3d_shader; //the default shader program for all 3d objects
extern GLuint tt_std_2d_shader; //the default shader program for all 2d objects
extern bool tt_gfx_gouraud_shading_active; //toggle if gouraud shading is active
extern bool tt_gfx_phong_shading_active; //toggle if phong shading is active
extern bool tt_gfx_tone_mapping_toggle; //toggle if tone mapping is enabled
extern float tt_gfx_exposure; //full scene exposure

//returns true if successfull
bool tt_gfx_init()
{
	//creating the standard shaders
	tt_std_2d_shader=tt_gfx_create_shader(
		NULL,
		"shaders/std_2d_vertex.glsl",
		NULL,
		NULL,
		NULL,
		"shaders/std_2d_fragment.glsl");
	if(tt_std_2d_shader==0)
	{
		tt_log(TT_ERROR, "failed to create the standard 2d shader");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "successfully built the standard 2d shader");
	}

	tt_std_3d_shader=tt_gfx_create_shader(
		NULL,
		"shaders/std_3d_vertex.glsl",
		NULL,
		NULL,
		NULL,
		"shaders/std_3d_fragment.glsl");
	if(tt_std_3d_shader==0)
	{
		tt_log(TT_ERROR, "failed to create the standard 3d shader");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "successfully built the standard 3d shader");
	}
	
	//preparing the primitives to be able to create them faster on the fly
	tt_gfx_prepare_quad();
	tt_gfx_prepare_cube();
	tt_gfx_prepare_sprite();
	tt_gfx_3d_default_tex_init();
	tt_gfx_2d_default_tex_init();

	tt_gfx_camera_setup();
	tt_math_mat4_make_projection_matrix(
		&tt_perspective_projection_mat,
		tt_res_x,
		tt_res_y,
		tt_fov,
		tt_near_plane,
		tt_far_plane);

	glDepthFunc(GL_LESS);

	//setting lighting defaults
	tt_gfx_gouraud_shading_active=true; //activate gouraud shading
	tt_gfx_phong_shading_active=false;
	tt_gfx_tone_mapping_toggle=false;
	tt_gfx_exposure=1.0f;
	tt_gfx_directional_light_setup();
	tt_gfx_point_light_setup();
	tt_gfx_ao_light_setup();

	return true;
}
