#include <shooting-range.hpp>

int main(void)
{
	sr::sr sr; //starting the game
	sr::player player;

	for(int i=0; i<1000; i++)
	{
		sr.update();
	}
	return 0;
}

