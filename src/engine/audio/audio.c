#include <tt.h>

ALCdevice *device=NULL;
ALCcontext *context=NULL;

void tt_audio_init()
{
	tt_log(TT_INFO, "initializing OpenAL...");

	device=alcOpenDevice(NULL); //open default device
	if(!device)
	{
		tt_log(TT_ERROR, "there couldn't be any audio device found");
		tt_log(TT_WARN, "continue without audio");
		return;
	}

	context=alcCreateContext(device, NULL);
	if(!alcMakeContextCurrent(context))
	{
		tt_log(TT_ERROR, "context creation failed");
		tt_log(TT_WARN, "continue without audio");	
		return;
	}

	ALenum error=alGetError(); //reset the error stack

	tt_log(TT_INFO, "done");
}

void tt_audio_quit()
{
	tt_log(TT_INFO, "ending the audio system...");
	alcDestroyContext(context);
	alcCloseDevice(device);
	tt_log(TT_INFO, "done");
}

tt_3d_audio_source* tt_audio_3d_source_new()
{
	tt_3d_audio_source *new_source=malloc(sizeof(tt_3d_audio_source));
	if(!new_source)
	{
		tt_log(TT_ERROR, "couldn't allocate memory for a 3D audio source");
		return NULL;
	}
	ALenum error=alGetError();
	alGenSources(1, &new_source->source);
	error=alGetError();
	if(error==AL_OUT_OF_MEMORY)
	{
		tt_log(TT_ERROR, "OpenAL has not enough memory to allocate the audio source");
	}
	if(error==AL_INVALID_VALUE)
	{
		tt_log(TT_ERROR, "There are not enough non-memory resources or the source pointer is not valid");
	}
	if(error==AL_INVALID_OPERATION )
	{
		tt_log(TT_ERROR, "There is no valid context");
	}
	if(error!=AL_NO_ERROR)
	{
		tt_log(TT_ERROR, "error while creating a 3D audio source");
		return NULL;
	}

	//set default values for the audio source
	alSourcef(new_source->source, AL_PITCH, 1.0);
	alSourcef(new_source->source, AL_GAIN, 1.0);
	alSource3f(new_source->source, AL_POSITION, 0, 0, 0);
	alSource3f(new_source->source, AL_VELOCITY, 0, 0, 0);
	alSourcei(new_source->source, AL_LOOPING, AL_FALSE);
	alSourcef(new_source->source, AL_MIN_GAIN, 0.0);
	alSourcef(new_source->source, AL_MAX_GAIN, 1000.0);
	alSourcePlay(new_source->source); //sets the AL_SOURCE_STATE to AL_STOPPED

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
		tt_log(TT_ERROR, "couldn't allocate memory for a new sound");
		return NULL;		
	}
	alGenBuffers(1, &new_sound->buffer);
	ALenum error=alGetError();
	if(error!=AL_NO_ERROR)
	{
		free(new_sound);
		tt_log(TT_ERROR, "error while creating a new buffer for a sound");
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
		tt_log(TT_ERROR, "error while buffering a new sound");
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

	if(new_sound)
	{
		tt_log(TT_INFO, "audio file successfully read from %s", path);
		//default values
		new_sound->gain=1.0;
	}
	else
	{
		tt_log(TT_ERROR, "error while reading audio file from %s", path);
	}
	return new_sound;
}

void tt_audio_set_sound_gain(tt_sound *sound, const float gain)
{
	sound->gain=gain;
}

void tt_audio_buffer_sound_for_3d_source(
	tt_sound *sound,
	tt_3d_audio_source *source)
{
	if(sound && source)
	{
		alSourcei(source->source, AL_BUFFER, sound->buffer);
		alGetError();
		alSourcef(source->source, AL_GAIN, sound->gain);
		ALenum error=alGetError();
		if(error!=AL_NO_ERROR)
		{
			tt_log(TT_ERROR, "couldn't set gain for sound");
		}
	}
	else
	{
		tt_log(TT_ERROR, "a sound and a 3D audio source need to exist");
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
		tt_log(TT_ERROR, "a 3D audio source need to exist otherwise no sound can be played");
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

bool tt_audio_is_source_playing(tt_3d_audio_source *source)
{
	ALenum error=alGetError();
	ALint value;
	alGetSourcei(source->source, AL_SOURCE_STATE, &value);
	error=alGetError();
	if(value==AL_STOPPED)
	{
		return false;
	}
	switch(error)
	{
		case AL_INVALID_VALUE:
			tt_log(TT_ERROR, "invalid value pointer was given to OpenAL");
			break;

		case AL_INVALID_ENUM:
			tt_log(TT_ERROR, "invalid enum value was given to OpenAL");
			break;

		case AL_INVALID_NAME:
			tt_log(TT_ERROR, "invalid source name was given to OpenAL");
			break;

		case AL_INVALID_OPERATION:
			tt_log(TT_ERROR, "invalid context within OpenAL");
			break;
	}
	return true;
}

void tt_audio_set_global_gain(float volume)
{
	alGetError();
	alListenerf(AL_GAIN, volume);
	ALenum error=alGetError();
	if(error!=AL_NO_ERROR)
	{
		tt_log(TT_ERROR, "the global volume couldn't be set");
		return;
	}
	tt_log(TT_INFO, "global gain was set to %f", volume);
}
