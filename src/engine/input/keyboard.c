#include <tt.h>

const uint8_t *keyboard_state=NULL;

#define KEY_MAX_PRESSES_SIMULTANIOUS 10
#define NO_KEY_PRESS 0

uint8_t keyboard_press[KEY_MAX_PRESSES_SIMULTANIOUS];

void tt_input_keyboard_update()
{
	keyboard_state=SDL_GetKeyboardState(NULL);

	//reset key presses
	for(int i=0; i<KEY_MAX_PRESSES_SIMULTANIOUS; i++)
	{
		keyboard_press[i]=NO_KEY_PRESS;
	}
}

void tt_input_keyboard_press_update(SDL_Event event)
{
	if(	event.type==SDL_KEYDOWN &&
		event.key.state==SDL_PRESSED &&
		event.key.repeat==0)
	{
		for(int i=0; i<KEY_MAX_PRESSES_SIMULTANIOUS; i++)
		{
			if(keyboard_press[i]==NO_KEY_PRESS)
			{
				keyboard_press[i]=event.key.keysym.scancode;
				break;
			}
		}
	}
}

bool tt_input_keyboard_key_down(const unsigned char key)
{
	return keyboard_state[key];
}

bool tt_input_keyboard_key_press(const unsigned char key)
{
	for(int i=0; i<KEY_MAX_PRESSES_SIMULTANIOUS; i++)
	{
		if(keyboard_press[i]==key)
		{
			return true;
		}
	}
	return false;
}
