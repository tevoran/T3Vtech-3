#ifndef TT_INPUT_H
#define TT_INPUT_H

#include <tt.h>

void tt_input_update();


//mouse
void tt_input_mouse_set_relative_mode(const bool toggle);
void tt_input_mouse_update(const SDL_Event event);

void tt_input_mouse_relative_motion(
	int *x_relative,
	int *y_relative);

#endif