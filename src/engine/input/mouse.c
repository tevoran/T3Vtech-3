#include <tt.h>

extern SDL_Window *tt_window; //game window
extern uint32_t tt_res_x; //game resolution
extern uint32_t tt_res_y; //game resolution

//relative mouse motion mode
bool mouse_relative_mode_toggle=false; //is the mouse staying in one place?
int delta_x=0; //the mouse movement relative to last frame
int delta_y=0; //the mouse movement relative to last frame
bool mouse_motion_read=true; //if the current mouse motion is not read yet
	//it can be read

//mouse buttons
#define SUPPORTET_BUTTONS 5
unsigned char mouse_button[SUPPORTET_BUTTONS]; //SDL supports apparently only 5 mouse buttons

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

	if(event.type==SDL_MOUSEBUTTONDOWN)
	{
		switch(event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				mouse_button[TT_MOUSE_LEFT]=1;
				break;
			}
			case SDL_BUTTON_MIDDLE:
			{
				mouse_button[TT_MOUSE_MIDDLE]=1;
				break;
			}
			case SDL_BUTTON_RIGHT:
			{
				mouse_button[TT_MOUSE_RIGHT]=1;
				break;
			}
			case SDL_BUTTON_X1:
			{
				mouse_button[TT_MOUSE_X1]=1;
				break;
			}
			case SDL_BUTTON_X2:
			{
				mouse_button[TT_MOUSE_X2]=1;
				break;
			}
			default:
			{

			}
		}
	}
	else
	{
		//reset mouse buttons to not pressed
		for(int i=0; i<SUPPORTET_BUTTONS; i++)
		{
			mouse_button[i]=0;
		}		
	}
}

//this only works if the relative mode is set
void tt_input_mouse_relative_motion(
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

bool tt_input_mouse_button_down(const unsigned char button)
{
	return mouse_button[button];
}