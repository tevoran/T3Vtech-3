#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 768, false);

	for(int i=0; i<1000; i++)
	{
		tt_new_frame();		
	}
	//SDL_Delay(3000);


	return 0;
}