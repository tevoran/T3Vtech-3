#include <tt.h>

//global stuff
//all global variables should only be in this file to avoid
//the dangers that are associated with global variables


//general stuff

//SDL
SDL_Window *tt_window=NULL; //game window
uint32_t tt_res_x; //game resolution
uint32_t tt_res_y; //game resolution
uint32_t tt_desktop_res_x; //desktop resolution
uint32_t tt_desktop_res_y; //desktop resolution
SDL_GLContext tt_glcontext; //OpenGL context for SDL2
SDL_Event tt_event; //SDL events

//shaders
GLuint tt_std_3d_shader; //the default shader program for all 3d objects
GLuint tt_std_2d_shader; //the default shader program for all 2d objects

//2D renderer stuff
T_node *tt_2d_list_entry_node=NULL;
T_node *tt_2d_list_last_entry=NULL;

//3D renderer stuff
float tt_near_plane=0.1; //near clipping plane
float tt_far_plane=1000; //far clipping plane
float tt_fov=0.5*tt_PI; //field of view in radians
tt_mat4 tt_perspective_projection_mat; //the 3D perspective projection matrix
T_node *tt_3d_list_entry_node=NULL; //start of the 3D object rendering list

//lighting
bool tt_gfx_gouraud_shading_active=true; //toggle if gouraud shading is active
bool tt_gfx_phong_shading_active=true; //toggle if phong shading is active
GLuint tt_gfx_ubo_dir_light; //uniform buffer object with directional light data
GLuint tt_gfx_ubo_point_light; //uniform buffer object for point light data
GLuint tt_gfx_ubo_ao_light; //uniform buffer object for ao light data
	//ambient lighting
	float tt_gfx_amb_light_strength=0.33; //the ambient light strength
	tt_vec3 tt_gfx_amb_light_color={1.0,1.0,1.0}; //the ambient light color

//global settings
bool tt_gfx_tone_mapping_toggle=false;
float tt_gfx_exposure=1.0; //full scene exposure
float tt_gfx_saturation=1.0; //full scene saturation
float tt_gfx_contrast=1.0; //full scene contrast

//camera
tt_mat4 tt_camera_position; //current camera position
tt_mat4 tt_camera_rotation; //current camera rotation

//primitives
//Here are prepared primitives. They are already created after the initialization
//and will be used when "creating" primitives to save time.

//2D
GLuint tt_gfx_2d_default_tex; //default texture


//3D
//default texture
GLuint tt_gfx_3d_default_tex;

//quad
GLuint tt_gfx_3d_quad_vao;
GLuint tt_gfx_3d_quad_vbo;
GLuint tt_gfx_3d_quad_ibo;

//cube
GLuint tt_gfx_3d_cube_vao;
GLuint tt_gfx_3d_cube_vbo;
GLuint tt_gfx_3d_cube_ibo;

//2D
//sprite
GLuint tt_gfx_2d_sprite_vao;
GLuint tt_gfx_2d_sprite_vbo;
GLuint tt_gfx_2d_sprite_ibo;