#ifndef TT_H
#define TT_H

#ifdef __cplusplus
	extern "C" {
#endif

//stdlib
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <limits.h>


//vendor
#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <stb_image.h>
#include <al.h>
#include <alc.h>

//engine headers
#include <math/math.h>
		
#include <common/init.h>
#include <common/quit.h>
#include <common/list.h>
#include <common/new_frame.h>
#include <common/time.h>
#include <common/color.h>
#include <common/collision/3D/collision.h>

#include <gfx/gfx.h>
#include <audio/audio.h>
#include <input/input.h>
#include <debug/logging.h>
		
#ifdef __cplusplus
	}
#endif

#endif /* TT_H */
