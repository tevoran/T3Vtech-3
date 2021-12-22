#include <ttmv.hpp>

ttmv::sys::sys()
{
	std::cout << "TTVM\n";
	tt_init("TTMV", 720,720, false, true);
}
