#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1920, 1080, true);

	for(int i=0; i<600; i++)
	{
		tt_new_frame();		
	}
	//SDL_Delay(3000);


	return 0;
}