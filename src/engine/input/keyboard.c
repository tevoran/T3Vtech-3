#include <tt.h>

const uint8_t *keyboard_state=NULL;

void tt_input_keyboard_update()
{
	keyboard_state=SDL_GetKeyboardState(NULL);
}

bool tt_input_keyboard_key_pressed(const unsigned char key)
{
	return keyboard_state[key];
}