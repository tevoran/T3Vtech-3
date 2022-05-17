#ifndef TT_AUDIO_H
#define TT_AUDIO_H

#include <tt.h>

struct tt_3d_audio_source
{
	ALuint source;
} typedef tt_3d_audio_source;

struct tt_sound
{
	ALuint buffer;
	float gain;
} typedef tt_sound;

//engine audio functions
void tt_audio_init();
void tt_audio_quit();

//file reading functions
void tt_audio_load_wav(
	const char *path,
	void **data,
	int *size_of_data,
	int *frequency,
	bool *stereo);

//user functions
tt_3d_audio_source* tt_audio_3d_source_new();
void tt_audio_3d_source_delete(tt_3d_audio_source **source);
tt_sound* tt_audio_sound_from_data(
	const void *data,
	const int size_of_data,
	const int frequency,
	const bool stereo);
tt_sound* tt_audio_sound_from_file(const char *path);
void tt_audio_buffer_sound_for_3d_source(
	tt_sound *sound,
	tt_3d_audio_source *source);
void tt_audio_set_sound_gain(tt_sound *sound, const float gain);
void tt_audio_play_3d_source(tt_3d_audio_source *source);
void tt_audio_loop_3d_source(tt_3d_audio_source *source, const bool loop_toggle);

void tt_audio_set_global_gain(float volume);

#endif