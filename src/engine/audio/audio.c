#include <tt.h>

extern bool tt_quiet; //this activates/deactivates debug messages

ALCdevice *device=NULL;
ALCcontext *context=NULL;

void tt_audio_init()
{
	if(!tt_quiet)
	{
		printf("initializing OpenAL...");
	}

	device=alcOpenDevice(NULL); //open default device
	if(!device)
	{
		printf("[ERROR] there couldn't be any audio device found\n");
		printf("[ERROR] continue without audio\n");
		return;
	}

	context=alcCreateContext(device, NULL);
	if(!alcMakeContextCurrent(context))
	{
		printf("[ERROR] context creation failed\n");
		printf("[ERROR] continue without audio\n");	
		return;
	}

	ALenum error=alGetError(); //reset the error stack

	if(!tt_quiet)
	{
		printf("done\n");
	}
}

void tt_audio_quit()
{
	if(!tt_quiet)
	{
		printf("ending the audio system...");
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
	if(!tt_quiet)
	{
		printf("done\n");
	}
}

tt_3d_audio_source* tt_audio_3d_source_new()
{
	tt_3d_audio_source *new_source=malloc(sizeof(tt_3d_audio_source));
	if(!new_source)
	{
		printf("[ERROR] couldn't allocate memory for a 3D audio source\n");
		return NULL;
	}
	alGenSources(1, &new_source->source);
	ALenum error=alGetError();
	if(error!=AL_NO_ERROR)
	{
		printf("[ERROR] error while creating a 3D audio source\n");
		return NULL;
	}

	//set default values for the audio source
	alSourcef(new_source->source, AL_PITCH, 1.0);
	alSourcef(new_source->source, AL_GAIN, 1.0);
	alSource3f(new_source->source, AL_POSITION, 0, 0, 0);
	alSource3f(new_source->source, AL_VELOCITY, 0, 0, 0);
	alSourcei(new_source->source, AL_LOOPING, AL_FALSE);

	return new_source;
}

void tt_audio_3d_source_delete(tt_3d_audio_source **source)
{
	if(*source==NULL)
	{
		return;
	}

	alDeleteSources(1, &(*source)->source);

	free(*source);
	*source=NULL; //mark source as deleted
}

tt_sound* tt_audio_sound_from_data(
	const void *data,
	const int size_of_data,
	const int frequency,
	const bool stereo)
{
	tt_sound *new_sound=malloc(sizeof(tt_sound));
	if(!new_sound)
	{
		printf("[ERROR] couldn't allocate memory for a new sound\n");
		return NULL;		
	}
	alGenBuffers(1, &new_sound->buffer);
	ALenum error=alGetError();
	if(error!=AL_NO_ERROR)
	{
		free(new_sound);
		printf("[ERROR] error while creating a new buffer for a sound\n");
		return NULL;
	}
	if(stereo)
	{
		alBufferData(new_sound->buffer, AL_FORMAT_STEREO16, data, size_of_data, frequency);
	}
	else
	{
		alBufferData(new_sound->buffer, AL_FORMAT_MONO16, data, size_of_data, frequency);
	}
	if(error!=AL_NO_ERROR)
	{
		free(new_sound);
		printf("[ERROR] error while buffering a new sound\n");
		return NULL;
	}
	return new_sound;
}

tt_sound* tt_audio_sound_from_file(const char *path)
{
	void *data=NULL;
	int size_of_data=0;
	int frequency=0;
	bool stereo=false;

	if(strstr(path, ".wav"))
	{
		tt_audio_load_wav(path, &data, &size_of_data, &frequency, &stereo);
	}

	tt_sound *new_sound=NULL;
	if(data)
	{
		new_sound=tt_audio_sound_from_data(
			data,
			size_of_data,
			frequency,
			stereo);	
	}

	//printf("data: %x\nsize_of_data: %u\nfrequency: %u\n", data, size_of_data, frequency);
	if(new_sound)
	{
		printf("audio file successfully read from %s\n", path);
	}
	else
	{
		printf("[ERROR] error while reading audio file from %s\n", path);
	}
	return new_sound;
}

void tt_audio_buffer_sound_for_3d_source(
	tt_sound *sound,
	tt_3d_audio_source *source)
{
	if(sound && source)
	{
		alSourcei(source->source, AL_BUFFER, sound->buffer);
	}
	else
	{
		printf("[ERROR] a sound and a 3D audio source need to exist\n");
	}
}

void tt_audio_play_3d_source(tt_3d_audio_source *source)
{
	if(source)
	{
		alSourcePlay(source->source);			
	}
	else
	{
		printf("[ERROR] a 3D audio source need to exist otherwise no sound can be played\n");
	}
}

void tt_audio_loop_3d_source(tt_3d_audio_source *source, const bool loop_toggle)
{
	if(!source)
	{
		return;	
	}
	if(loop_toggle)
	{
		alSourcei(source->source, AL_LOOPING, AL_TRUE);
	}
	else
	{
		alSourcei(source->source, AL_LOOPING, AL_FALSE);
	}
}