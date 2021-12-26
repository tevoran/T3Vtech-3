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

	//creating the shooting range world
	m_range=new world;

	tt_input_mouse_set_relative_mode(true); //necessary for FPS mouse movement

}

sr::sr::~sr()
{
	//cleaning up the resources

}

void sr::sr::update()
{
	tt_vec3 rot_axis={0,1,0};
	tt_camera_rotate(&rot_axis, 0.01);
	tt_new_frame();
}