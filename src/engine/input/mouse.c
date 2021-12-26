#include <tt.h>

//set relative mode where only relative mouse motion gets captured
void tt_input_mouse_set_relative_mode(const bool toggle)
{
	if(toggle)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);		
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);			
	}
}

void tt_input_mouse_update(SDL_Event event)
{
	if(event.type==SDL_MOUSEMOTION)
	{
		printf("mouse\n");
	}
}
