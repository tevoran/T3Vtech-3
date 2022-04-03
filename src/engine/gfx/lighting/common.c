#include <tt.h>

extern bool tt_gfx_gouraud_shading_active; //toggle if gouraud shading is active
extern bool tt_gfx_phong_shading_active; //toggle if phong shading is active


//Gouraud Shading
void tt_gfx_gouraud_shading(bool active)
{
	tt_gfx_gouraud_shading_active=active;
}

//Phong Shading
void tt_gfx_phong_shading(bool active) {
	tt_gfx_phong_shading_active=active;
}
