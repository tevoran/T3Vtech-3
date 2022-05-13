#include <tt.h>

extern SDL_Window *tt_window;
extern uint32_t tt_desktop_res_x;
extern uint32_t tt_desktop_res_y;
extern SDL_GLContext tt_glcontext;

void tt_quit(void)
{
	//quitting the audio system
	tt_audio_quit();

	//quitting the graphics system
	tt_gfx_quit();

	//resetting the window size to the desktop resolution to
	//avoid strange resolution issues after closing the game
	SDL_SetWindowSize(
		tt_window,
		tt_desktop_res_x,
		tt_desktop_res_y);

	tt_log(TT_INFO, "destroying SDL2 OpenGL context...");
		SDL_GL_DeleteContext(tt_glcontext);
	tt_log(TT_INFO, "done");

	tt_log(TT_INFO, "destroying SDL window...");
		SDL_DestroyWindow(tt_window);
	tt_log(TT_INFO, "done");

	tt_log(TT_INFO, "quitting SDL2_ttf...");
		TTF_Quit();
	tt_log(TT_INFO, "done");

	tt_log(TT_INFO, "quitting SDL2...");
		SDL_Quit();
	tt_log(TT_INFO, "done");
}