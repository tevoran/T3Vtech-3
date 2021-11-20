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
GLuint tt_std_3d_shader; //the default shader for all 3d objects
GLuint tt_std_2d_shader; //the default shader for all 2d objects