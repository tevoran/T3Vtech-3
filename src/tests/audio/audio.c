#include <tt.h>

int main(int argc, char *argv[])
{
	tt_init("T3Vtech3 test window", 1920, 1080, false, 16, NULL);

	printf("Create first source\n");
	tt_3d_audio_source *source = tt_audio_3d_source_new();
	if(source)
	{
		printf("Audio source successfully created\n");
	}

	tt_sound *sound = tt_audio_sound_from_file("assets/audio/test-moo.wav");
	if(sound)
	{
		printf("Audio file could be successfully loaded\n");
	}

	tt_audio_buffer_sound_for_3d_source(sound, source);
	tt_audio_play_3d_source(source);

	printf("Create second source\n");
	tt_3d_audio_source *source_2 = tt_audio_3d_source_new();
	if(source_2)
	{
		printf("Audio source successfully created\n");
	}

	tt_sound *sound_2 = tt_audio_sound_from_file("assets/audio/test-moo.wav");
	if(sound_2)
	{
		printf("Audio file could be successfully loaded\n");
	}

	tt_audio_buffer_sound_for_3d_source(sound_2, source_2);
	SDL_Delay(5000);
	tt_audio_play_3d_source(source_2);

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		tt_new_frame();
	}

	return 0;
}