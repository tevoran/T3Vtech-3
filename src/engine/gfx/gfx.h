#ifndef TT_GFX_H
#define TT_GFX_H

#include <tt.h>
#include "vertex.h"
#include "shaders.h"
#include "camera.h"
#include "renderer/renderer.h"
#include "lighting/lighting.h"
#include "objects/fonts/fonts.h"
#include "objects/3d/textures/textures.h"
#include "objects/3d/objects/objects.h"
#include "objects/3d/objects/batch_objects/batch_object.h"
#include "objects/2d/textures/textures.h"
#include "objects/2d/objects/objects.h"

bool tt_gfx_init(); //returns true if successfull
uint32_t tt_gfx_get_window_width();
uint32_t tt_gfx_get_window_height();
tt_vec2 tt_gfx_pixels_to_screen_space(const tt_vec2 *v);

//cleaning up what was initalized by the graphics system
void tt_gfx_quit();

#endif