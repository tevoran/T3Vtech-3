#include <tt.h>

extern bool tt_quiet; //this activates/deactivates debug messages

tt_font* tt_font_open(
	const char *filename,
	const int size_pt)
{
	tt_font *new_font=malloc(sizeof(tt_font));
	if(!tt_quiet)
	{
		printf("reading font from %s\n", filename);
	}
	new_font->font=TTF_OpenFont(filename, size_pt);
	if(new_font->font)
	{
		if(!tt_quiet)
		{
			printf("successfully read font from %s\n", filename);
		}
		return new_font;		
	}
	else
	{
		printf("[ERROR] couldn't read font from %s\n", filename);
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
