#include <shooting-range.hpp>

int main(int argc, char *argv[])
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

