#include <shooting-range.hpp>

int main(void)
{
	sr::sr sr; //starting the game
	sr::player player;

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		player.update();
		sr.update();
	}
	return 0;
}

