#include <tt.h>

extern SDL_Window *tt_window;

//return true if successful
bool tt_init(
	const char* window_name,
	uint32_t res_x, 
	uint32_t res_y,
	bool fullscreen)
{

	printf("initialize T3Vtech 3 engine\n");

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
	

	if(fullscreen)
	{
		tt_window=SDL_CreateWindow(
			"T3Vtech3", 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			res_x, res_y,
			SDL_WINDOW_FULLSCREEN |
			SDL_WINDOW_OPENGL);		
	}
	else
	{
		tt_window=SDL_CreateWindow(
			"T3Vtech3", 
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
	}

	return true;
}