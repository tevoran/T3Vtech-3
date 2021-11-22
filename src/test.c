#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 720, false);

	tt_3d_object *quad=tt_new_quad();
	
	for(int i=0; i<600; i++)
	{
		tt_new_frame();		
	}


	return 0;
}