#include <tt.h>

extern bool tt_quiet; //this activates/deactivates debug messages
extern SDL_Window *tt_window;
extern uint32_t tt_desktop_res_x;
extern uint32_t tt_desktop_res_y;
extern SDL_GLContext tt_glcontext;

void tt_quit(void)
{
	//quitting the graphics system
	tt_gfx_quit(tt_quiet);

	//resetting the window size to the desktop resolution to
	//avoid strange resolution issues after closing the game
	SDL_SetWindowSize(
		tt_window,
		tt_desktop_res_x,
		tt_desktop_res_y);

	if(!tt_quiet)
	{
		printf("destroying SDL2 OpenGL context...");
	}
		SDL_GL_DeleteContext(tt_glcontext);
	if(!tt_quiet)
	{
		printf("done\n");
	}

	if(!tt_quiet)
	{
		printf("destroying SDL window...");
	}
		SDL_DestroyWindow(tt_window);
	if(!tt_quiet)
	{
		printf("done\n");
	}

	if(!tt_quiet)
	{
		printf("quitting SDL2_ttf...");
	}
		TTF_Quit();
	if(!tt_quiet)
	{
		printf("done\n");
	}	

	if(!tt_quiet)
	{
		printf("quitting SDL2...");
	}
		SDL_Quit();
	if(!tt_quiet)
	{
		printf("done\n");
	}
}