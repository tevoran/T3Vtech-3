#include <tt.h>

extern SDL_Event tt_event; //SDL events

void tt_input_update()
{
	while(SDL_PollEvent(&tt_event))
	{
		//mouse event
		tt_input_mouse_update(tt_event);
	}
}