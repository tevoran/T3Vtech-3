#include <tt.h>

extern SDL_Window *tt_window; //game window
extern uint32_t tt_res_x; //game resolution
extern uint32_t tt_res_y; //game resolution

bool mouse_relative_mode_toggle=false; //is the mouse staying in one place?
int delta_x=0; //the mouse movement relative to last frame
int delta_y=0; //the mouse movement relative to last frame
bool mouse_motion_read=true; //if the current mouse motion is not read yet
	//it can be read


//set relative mode where only relative mouse motion gets captured
void tt_input_mouse_set_relative_mode(const bool toggle)
{
	if(toggle)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mouse_relative_mode_toggle=true;	
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		mouse_relative_mode_toggle=false;	
	}
}

void tt_input_mouse_update(const SDL_Event event)
{
	if(event.type==SDL_MOUSEMOTION)
	{
		mouse_motion_read=false;
		delta_x=event.motion.xrel;
		delta_y=event.motion.yrel;
	}
}

//this only works if the relative mode is set
void tt_input_mouse_relative(
	int *x_relative,
	int *y_relative)
{
	if(	mouse_relative_mode_toggle &&
		!mouse_motion_read)
	{
		mouse_motion_read=true;
		*x_relative=delta_x;
		*y_relative=delta_y;
	}
	else
	{
		*x_relative=0;
		*y_relative=0;
	}
}

