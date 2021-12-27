#include <shooting-range.hpp>

int main(void)
{
	sr::sr sr; //starting the game
	sr::player player;

	while(!tt_input_keyboard_key_pressed(TT_KEY_ESC))
	{
		player.update();
		sr.update(player.side_angle, player.up_angle);
	}
	return 0;
}

