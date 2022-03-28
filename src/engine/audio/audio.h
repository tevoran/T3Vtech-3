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
} typedef tt_sound;

//engine audio functions
void tt_audio_init();
void tt_audio_quit();

//user functions
tt_3d_audio_source* tt_audio_3d_source_new();
tt_sound* tt_audio_sound_from_data(
	const void *data,
	const int size_of_data,
	const int frequency,
	const bool stereo);
void tt_audio_buffer_sound_for_3d_source(
	tt_sound *sound,
	tt_3d_audio_source *source);
void tt_audio_play_3d_source(tt_3d_audio_source *source);

#endif