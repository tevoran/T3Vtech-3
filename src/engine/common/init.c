#include <tt.h>

extern SDL_Window *tt_window;
extern uint32_t tt_res_x;
extern uint32_t tt_res_y;
extern uint32_t tt_desktop_res_x;
extern uint32_t tt_desktop_res_y;
extern SDL_GLContext tt_glcontext;

//return true if successful
bool tt_init(
	const char *window_name,
	const uint32_t res_x, 
	const uint32_t res_y,
	const bool fullscreen)
{

	printf("initialize T3Vtech 3 engine\n");
	tt_res_x=res_x;
	tt_res_y=res_y;

	//zero as return value means everything is fine
	if(0!=SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO |
		SDL_INIT_EVENTS))
	{
		printf("[ERROR] couldn't initialize SDL2\n");
		return false;
	}
	else
	{
		printf("SDL2 initialized\n");
	}
	

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	tt_desktop_res_x=dm.w;
	tt_desktop_res_y=dm.h;
	printf(
		"desktop resolution is %ix%i at %iHz\n",
		tt_desktop_res_x,
		tt_desktop_res_y,
		dm.refresh_rate);

	if(fullscreen)
	{
		tt_window=SDL_CreateWindow(
			window_name, 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			res_x, res_y,
			SDL_WINDOW_FULLSCREEN |
			SDL_WINDOW_OPENGL);		
	}
	else
	{
		tt_window=SDL_CreateWindow(
			window_name, 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			res_x, res_y,
			SDL_WINDOW_OPENGL);		
	}
	if(tt_window==NULL)
	{
		printf("[ERROR] couldn't create a SDL2 window\n");
		return false;
	}
	else
	{
		printf("SDL2 window created\n");
		printf(
			"game resolution is %ix%i\n",
			tt_res_x,
			tt_res_y);
	}

	tt_glcontext=SDL_GL_CreateContext(tt_window);
	if(tt_glcontext==NULL)
	{
		printf("[ERROR] couldn't create OpenGL context\n");
	}
	else
	{
		printf("SDL2 OpenGL context created\n");
	}

	SDL_DisableScreenSaver();

	atexit(tt_quit);

	return true;
}