#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, NULL);

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		tt_new_frame();
	}

	return 0;
}