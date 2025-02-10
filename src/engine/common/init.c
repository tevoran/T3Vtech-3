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
	const bool fullscreen,
	const int msaa,
	const char *logging_file)
{
	//if no logging file is specified set a default one
	if(logging_file==NULL)
	{
		tt_log_open_log_file("T3Vtech-3.log");
	}
	else
	{
		tt_log_open_log_file(logging_file);
	}

	tt_log(TT_INFO, "initialize T3Vtech-3 engine");
	tt_res_x=res_x;
	tt_res_y=res_y;

	//detect platform
	#ifdef _WIN32
		tt_log(TT_INFO, "platform is Windows");
	#elif __linux__
		tt_log(TT_INFO, "platform is Linux");
	#else
		tt_log(TT_INFO, "unknown platform");
	#endif

	//zero as return value means everything is fine
	if(0!=SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_VIDEO |
		SDL_INIT_EVENTS|
		SDL_INIT_GAMECONTROLLER))
	{
		tt_log(TT_ERROR, "couldn't initialize SDL2");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "SDL2 initialized");
	}

	//if antialiasing with msaa is requested
	//then set SDL to what is necessary
	if(msaa>1)
	{
		tt_log(TT_INFO, "activating %ix MSAA", msaa);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa);
	}

	//get current desktop resolution to avoid resolution errors
	//at the end of execution of the game
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	tt_desktop_res_x=dm.w;
	tt_desktop_res_y=dm.h;
	tt_log(TT_INFO,
		"desktop resolution is %ix%i at %iHz",
		tt_desktop_res_x,
		tt_desktop_res_y,
		dm.refresh_rate);

	if(fullscreen)
	{
		int num_displays = SDL_GetNumVideoDisplays();
		tt_log(TT_INFO, "SDL_GetNumVideoDisplays(): %i", num_displays);

		tt_window=SDL_CreateWindow(
			window_name,
			0,
			0,
			0, 0,
			SDL_WINDOW_FULLSCREEN_DESKTOP |
			SDL_WINDOW_BORDERLESS |
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
		tt_log(TT_ERROR, "couldn't create a SDL2 window");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "SDL2 window created");
		tt_log(TT_INFO,
			"game resolution is %ix%i",
			tt_res_x,
			tt_res_y);
	}

	//setting the desired OpenGL version
	tt_log(TT_INFO, "using OpenGL 4.3");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	tt_glcontext=SDL_GL_CreateContext(tt_window);
	if(tt_glcontext==NULL)
	{
		tt_log(TT_ERROR, "couldn't create OpenGL context");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "SDL2 OpenGL context created");
	}


	if(glewInit()!=GLEW_OK)
	{
		tt_log(TT_ERROR, "GLEW couldn't be initialized");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "GLEW initialized");
	}

	SDL_DisableScreenSaver();
	tt_log(TT_INFO,"active OpenGL extensions: %s", glGetString(GL_EXTENSIONS));

	if(TTF_Init()!=0)
	{
		tt_log(TT_ERROR, "SDL2_ttf couldn't be initialized");
		tt_log(TT_ERROR, "error message: %s", TTF_GetError());
	}
	else
	{
		tt_log(TT_INFO, "SDL2_ttf initialized");
	}

	//making sure tt_quit gets called when game is closed
	atexit(tt_quit);

	if(!tt_gfx_init())
	{
		tt_log(TT_ERROR, "couldn't set up the GFX functionalities of T3Vtech-3");
		return false;
	}
	else
	{
		tt_log(TT_INFO, "GFX functionalities initialized");
	}

	//activate MSAA, if requested
	if(msaa>1)
	{
		glEnable(GL_MULTISAMPLE);
	}

	//initializing input devices
	//preparing keyboard to avoid nullptr dereferencing
	tt_input_keyboard_update();
	tt_input_mouse_init();
	tt_input_controller_add_mappings();

	//init time
	tt_time_init();

	tt_audio_init();

	return true;
}
