#include <ttmv.hpp>

int main(int argc, char *argv[])
{
	ttmv::sys sys(argc, argv);

	for(int i=0; i<200; i++)
	{
		tt_new_frame();
	}
	return 0;
}