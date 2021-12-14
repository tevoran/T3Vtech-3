#include <tt.h>

//global stuff
//all global variables should only be in this file to avoid
//the dangers associated with global variables


//general stuff
SDL_Window *tt_window=NULL; //game window
uint32_t tt_res_x; //game resolution
uint32_t tt_res_y; //game resolution
uint32_t tt_desktop_res_x; //desktop resolution
uint32_t tt_desktop_res_y; //desktop resolution
SDL_GLContext tt_glcontext; //OpenGL context for SDL2

//shaders
GLuint tt_std_3d_shader; //the default shader program for all 3d objects
GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//3D renderer stuff
float tt_near_plane=0.1; //near clipping plane
float tt_far_plane=1000; //far clipping plane
float tt_fov=0.5*tt_PI; //field of view in radians
tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix
tt_node *tt_3d_list_entry_node=NULL; //start of the 3D object rendering list

//lighting
bool tt_gfx_gouraud_shading_active=true; //toggle if gouraud shading is active
GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data
	//ambient lighting
	float tt_gfx_amb_light_strength=0.33; //the ambient light strength
	tt_vec3 tt_gfx_amb_light_color={1.0,1.0,1.0}; //the ambient light color

//camera
tt_mat4 tt_camera_position; //current camera position

//primitives
//Here are prepared primitives. They are already created after the initialization
//and will be used when "creating" primitives to save time.

//3D
//default texture
GLuint tt_gfx_3d_default_tex;

//quad
GLuint tt_gfx_3d_quad_vao;
GLuint tt_gfx_3d_quad_vbo;
GLuint tt_gfx_3d_quad_ibo;