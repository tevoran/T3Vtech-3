#pragma once

#include <tt.h>
#include <iostream>


namespace ttmv
{
	class sys
	{
	private:
		bool load_model=false;
		bool load_texture=false;

		//model
		tt_3d_object *model=NULL;
		tt_3d_custom_model *custom_model=NULL;
		tt_3d_texture *tex=NULL;

	public:
		sys(int argc, char *argv[]);
		~sys();
	};
}
