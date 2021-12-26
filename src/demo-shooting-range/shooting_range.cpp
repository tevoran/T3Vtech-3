#include <shooting-range.hpp>

sr::sr::sr()
{
	//setting up the engine
	std::cout << "Shooting Range Demo\n";
	tt_init(
		"T3Vtech-3 Shooting Range Demo",
		1920,
		1080,
		true,
		8,
		true);

	m_range=new world;
}

sr::sr::~sr()
{
	//cleaning up the resources

}

void sr::sr::update()
{
	tt_new_frame();
}