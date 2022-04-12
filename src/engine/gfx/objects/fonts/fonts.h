#ifndef TT_GFX_FONTS_2D_H
#define TT_GFX_FONTS_2D_H


#include <tt.h>

struct tt_font
{
	TTF_Font *font;
} typedef tt_font;

tt_font* tt_font_open(
	const char* filename,
	const int size_pt);
void tt_font_delete(tt_font **font);

#endif 