#include <tt.h>


void tt_gfx_render()
{
	//render 3D stuff
	tt_gfx_3d_preparation();
	tt_gfx_3d_render();

	//render 2D stuff
	tt_gfx_2d_preparation();
	tt_gfx_2d_render();
}
