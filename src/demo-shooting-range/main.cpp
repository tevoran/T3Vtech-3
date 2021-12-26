#include <shooting-range.hpp>

int main(void)
{
	sr::sr sr; //starting the game
	sr::player player;

	for(int i=0; i<1000; i++)
	{
		player.update();
		sr.update(player.side_angle, player.up_angle);
	}
	return 0;
}

