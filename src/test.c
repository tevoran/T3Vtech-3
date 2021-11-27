#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1366, 768, false);

	tt_vec3 pos={0.5,0.5,0.0};
	tt_vec3 scale={1,1,1};
	tt_vec3 orientation={0.5,0.5,0.0};
	tt_3d_object *quad=tt_3d_object_new();
	tt_3d_object_make_quad(quad);

	for(int i=0; i<180; i++)
	{
		tt_new_frame();
		SDL_Delay(15);

		scale.x=(float)i/90;
		tt_3d_object_scale(quad, &scale);

	}


	return 0;
}