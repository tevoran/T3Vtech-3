#ifndef TT_INPUT_H
#define TT_INPUT_H

#include <tt.h>
#include "keyboard_map.h"
#include "mouse_map.h"
#include "controller_map.h"

void tt_input_update();


//mouse
void tt_input_mouse_init();
void tt_input_mouse_set_relative_mode(const bool toggle);
void tt_input_mouse_update(const SDL_Event event);

void tt_input_mouse_button_reset();
void tt_input_mouse_relative_motion(
	int *x_relative,
	int *y_relative);
bool tt_input_mouse_button_press(const unsigned char button);
bool tt_input_mouse_button_down(const unsigned char button);
void tt_input_mouse_location(int *x, int *y);

//keyboard
void tt_input_keyboard_update();
void tt_input_keyboard_press_update(SDL_Event event);
bool tt_input_keyboard_key_down(const unsigned char key);
bool tt_input_keyboard_key_press(const unsigned char key);

//controller
void tt_input_controller_button_reset();
int tt_input_controller_count();
void tt_input_controller_add_new(SDL_Event event);
void tt_input_controller_removed(SDL_Event event);
void tt_input_controller_update(SDL_Event event);
void tt_input_controller_button_down_update(SDL_Event event);
void tt_input_controller_button_up_update(SDL_Event event);
void tt_input_controller_axis_update(SDL_Event event);

void tt_input_controller_add_mappings();

bool tt_input_controller_button_press(const int ctl_number, const unsigned char button);
bool tt_input_controller_button_down(const int ctl_number, const unsigned char button);
void tt_input_controller_axis_state(
	const int ctl_number, 
	float *l_stick_x_out,
	float *l_stick_y_out,
	float *r_stick_x_out,
	float *r_stick_y_out);

#endif