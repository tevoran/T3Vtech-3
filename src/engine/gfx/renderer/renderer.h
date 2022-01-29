#ifndef TT_GFX_RENDERER_H
#define TT_GFX_RENDERER_H

#include <tt.h>

void tt_gfx_render();

void tt_gfx_3d_preparation();
void tt_gfx_3d_render();
void tt_gfx_2d_preparation();
void tt_gfx_2d_render();

//3D stuff
void tt_set_fov(float radians);


#endif