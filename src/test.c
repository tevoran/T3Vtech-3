#include <tt.h>

int main()
{
	tt_init("T3Vtech3 test window", 1920, 1080, true);

	tt_vec3 pos={0.5,0.5,0.0};
	tt_vec3 orientation={0.5,0.5,0.0};
	tt_3d_object *quad=tt_new_quad(pos, orientation);

	tt_vec3 pos2={0.0,0.0,0.0};
	tt_3d_object *quad2=tt_new_quad(pos2, orientation);

	tt_vec3 pos3={-0.5,0.5,0.0};
	tt_3d_object *quad3=tt_new_quad(pos3, orientation);

	tt_vec3 pos4={-1.0,0.0,0.0};
	tt_3d_object *quad4=tt_new_quad(pos4, orientation);

	tt_vec3 pos5={-1.0,-1.0,0.0};
	tt_3d_object *quad5=tt_new_quad(pos5, orientation);

	tt_vec3 pos6={-0.5,-0.5,0.0};
	tt_3d_object *quad6=tt_new_quad(pos6, orientation);

	tt_vec3 pos7={-0.0,-1.0,0.0};
	tt_3d_object *quad7=tt_new_quad(pos7, orientation);

	tt_vec3 pos8={0.5,-0.5,0.0};
	tt_3d_object *quad8=tt_new_quad(pos8, orientation);
	
	for(int i=0; i<5; i++)
	{
		tt_new_frame();
		SDL_Delay(3000);		
	}


	return 0;
}