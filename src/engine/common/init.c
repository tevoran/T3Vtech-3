#include <tt.h>

extern bool tt_quiet; //this activates/deactivates debug messages
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
	const bool fullscreen,
	const int msaa,
	const bool quiet)
{
	tt_quiet=quiet;
	
	if(!quiet)
	{
		printf("initialize T3Vtech-3 engine\n");
	}
	tt_res_x=res_x;
	tt_res_y=res_y;

	//zero as return value means everything is fine
	if(0!=SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO |
		SDL_INIT_EVENTS|
		SDL_INIT_GAMECONTROLLER))
	{
		printf("[ERROR] couldn't initialize SDL2\n");
		return false;
	}
	else
	{
		if(!quiet)
		{
			printf("SDL2 initialized\n");
		}
	}
	
	//if antialiasing with msaa is requested
	//then set SDL to what is necessary
	if(msaa>1)
	{
		if(!quiet)
		{
			printf("activating %ix MSAA\n", msaa);
		}
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa);		
	}

	//get current desktop resolution to avoid resolution errors
	//at the end of execution of the game
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	tt_desktop_res_x=dm.w;
	tt_desktop_res_y=dm.h;
	if(!quiet)
	{
		printf(
			"desktop resolution is %ix%i at %iHz\n",
			tt_desktop_res_x,
			tt_desktop_res_y,
			dm.refresh_rate);		
	}

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
		if(!quiet)
		{
			printf("SDL2 window created\n");
			printf(
				"game resolution is %ix%i\n",
				tt_res_x,
				tt_res_y);
		}
	}

	tt_glcontext=SDL_GL_CreateContext(tt_window);
	if(tt_glcontext==NULL)
	{
		printf("[ERROR] couldn't create OpenGL context\n");
		return false;
	}
	else
	{
		if(!quiet)
		{
			printf("SDL2 OpenGL context created\n");
		}
	}


	if(glewInit()!=GLEW_OK)
	{
		printf("[ERROR] GLEW couldn't be initialized\n");
		return false;
	}
	else
	{
		if(!quiet)
		{
			printf("GLEW initialized\n");
		}
	}

	//setting the desired OpenGL version
	if(!quiet)
	{
		printf("using OpenGL 4.5\n");
	}
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_DisableScreenSaver();

	//making sure tt_quit gets called when game is closed
	atexit(tt_quit);

	if(!tt_gfx_init(quiet))
	{
		printf(
			"[ERROR] couldn't set up the GFX functionalities of T3Vtech-3\n");
		return false;
	}
	else
	{
		if(!quiet)
		{
			printf("GFX functionalities initialized\n");
		}
	}

	//activate MSAA, if requested
	if(msaa>1)
	{
		glEnable(GL_MULTISAMPLE); 
	}

	//preparing keyboard to avoid nullptr dereferencing
	tt_input_keyboard_update();

	return true;
}