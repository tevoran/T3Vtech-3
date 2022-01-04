#ifndef TT_INPUT_H
#define TT_INPUT_H

#include <tt.h>
#include "keyboard_map.h"
#include "mouse_map.h"

void tt_input_update();


//mouse
void tt_input_mouse_set_relative_mode(const bool toggle);
void tt_input_mouse_update(const SDL_Event event);

void tt_input_mouse_button_reset();
void tt_input_mouse_relative_motion(
	int *x_relative,
	int *y_relative);
bool tt_input_mouse_button_down(const unsigned char button);
void tt_input_mouse_location(int *x, int *y);

//keyboard
void tt_input_keyboard_update();
bool tt_input_keyboard_key_pressed(const unsigned char key);

//controller
void tt_input_controller_add_new(SDL_Event event);

void tt_input_controller_update(SDL_Event event);

#endif