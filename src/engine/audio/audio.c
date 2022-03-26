#include <tt.h>

void tt_audio_init()
{
	printf("initializing OpenAL...");

	ALCdevice *device;

	device = alcOpenDevice(NULL);
	if (!device)
	{
		printf("[ERROR] there couldn't be any audio device found\n");
	}

	printf("done\n");
}