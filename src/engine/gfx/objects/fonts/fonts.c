#include <tt.h>

tt_font* tt_font_open(
	const char *filename,
	const int size_pt)
{
	tt_font *new_font=malloc(sizeof(tt_font));
	tt_log(TT_INFO, "reading font from %s", filename);
	new_font->font=TTF_OpenFont(filename, size_pt);
	if(new_font->font)
	{
		tt_log(TT_INFO, "successfully read font from %s", filename);
		return new_font;		
	}
	else
	{
		tt_log(TT_ERROR, "couldn't read font from %s", filename);
		free(new_font);
		return NULL; //returning NULL if there is an error
	}
}

void tt_font_delete(tt_font **font)
{
	TTF_CloseFont((*font)->font);
	free(*font);
	*font=NULL; //marking the font as deleted
}
