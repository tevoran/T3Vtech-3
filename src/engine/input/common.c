#include <tt.h>

extern SDL_Event tt_event; //SDL events

void tt_input_update()
{

	tt_input_mouse_button_reset();
	while(SDL_PollEvent(&tt_event))
	{
		tt_input_mouse_update(tt_event);
		tt_input_keyboard_update();
	}
}