#include <shooting-range.hpp>

int main(void)
{
	sr::sr sr; //starting the game
	sr::player player;

	while(!tt_input_keyboard_key_pressed(TT_KEY_ESC))
	{
		//std::cout << tt_input_mouse_button_down(TT_MOUSE_RIGHT);
		player.update();
		sr.update();
	}
	return 0;
}

