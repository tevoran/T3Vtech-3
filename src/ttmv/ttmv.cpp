#include <ttmv.hpp>

int main(int argc, char *argv[])
{
	ttmv::sys sys(argc, argv);

	sys.loop(1000);
	return 0;
}