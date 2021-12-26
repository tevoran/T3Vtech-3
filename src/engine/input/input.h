#ifndef TT_INPUT_H
#define TT_INPUT_H

#include <tt.h>

void tt_input_update();


//mouse
void tt_input_mouse_set_relative_mode(const bool toggle);
void tt_input_mouse_update(SDL_Event event);


#endif