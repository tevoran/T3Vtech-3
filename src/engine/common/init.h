#ifndef TT_INIT_H
#define TT_INIT_H

#include <tt.h>

bool tt_init(
	const char *window_name,
	const uint32_t res_x, 
	const uint32_t res_y,
	const bool fullscreen,
	const bool quiet);

#endif