#include <tt.h>

extern SDL_Window *tt_window;
extern uint32_t tt_desktop_res_x;
extern uint32_t tt_desktop_res_y;
extern SDL_GLContext tt_glcontext;

void tt_quit()
{
	//resetting the window size to the desktop resolution to
	//avoid strange resolution issues after closing the game
	SDL_SetWindowSize(
		tt_window,
		tt_desktop_res_x,
		tt_desktop_res_y);

	printf("destroying SDL2 OpenGL context...");
		SDL_GL_DeleteContext(tt_glcontext);
	printf("done\n");

	printf("destroying SDL window...");
		SDL_DestroyWindow(tt_window);
	printf("done\n");

	printf("quitting SDL2...");
		SDL_Quit();
	printf("done\n");
}