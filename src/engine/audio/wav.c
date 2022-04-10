#include <tt.h>


//reads currently only 16 bit audio
void tt_audio_load_wav(
	const char *path,
	void **data,
	int *size_of_data,
	int *frequency,
	bool *stereo)
{
	FILE *file=fopen(path, "rb");
	if(!file)
	{
		printf("[ERROR] WAV file couldn't be read\n");
		return;
	}

	//reading header
	//RIFF mark check
	char riff_mark[5]; //+1 Byte for zero termination
	fgets(riff_mark, 5, file);
	if(!strstr(riff_mark, "RIFF"))
	{
		printf("[ERROR] the WAV file is missing the RIFF mark and is therefor not a WAV file\n");
		fclose(file);
		return;
	}

	//reading file size
	Uint32 file_size=0;
	fread(&file_size, 4, 1, file);
	printf("WAV file is %u kB\n", file_size/1024);

	//WAVE mark check
	char wave_mark[5]; //+1 Byte for zero termination
	fgets(wave_mark, 5, file);
	if(!strstr(wave_mark, "WAVE"))
	{
		printf("[ERROR] the WAV file is missing the WAVE mark and is therefor not a WAV file\n");
		fclose(file);
		return;
	}

	//format mark check
	char fmt_mark[5]; //+1 Byte for zero termination
	fgets(fmt_mark, 5, file);
	if(!strstr(fmt_mark, "fmt "))
	{
		printf("[ERROR] the WAV file is missing the format mark and is therefor not a WAV file\n");
		fclose(file);
		return;
	}

	//length of format data
	Uint32 format_length=0;
	fread(&format_length, 4, 1, file);
	if(format_length!=16)
	{
		printf("[ERROR] the format size is not correct. The file is corrupt.\n");
		fclose(file);
		return;
	}

	//check of format type
	Uint16 format_type=0;
	fread(&format_type, 2, 1, file);
	if(format_type!=1) //1 means PCM
	{
		printf("[ERROR] the format type is not correct.\n");
		fclose(file);
		return;
	}

	//number of channels
	Uint16 num_channels=0;
	fread(&num_channels, 2, 1, file);
	*stereo=num_channels;
	printf("number of channels in WAV file: %u\n", num_channels);

	//sample rate
	fread(frequency, 4, 1, file);
	printf("sample rate used in WAV file: %u\n", *frequency);

	//skipping unused values in header
	char unused[6];
	fread(unused, 6, 1, file);

	//bits per sample
	Uint16 bits_per_sample=0;
	fread(&bits_per_sample, 2, 1, file);
	printf("bits per sample used in WAV file: %u\n", bits_per_sample);
	if(bits_per_sample!=16)
	{
		printf("[WARNING] T3Vtech-3 currently uses only 16-bit audio\n");
	}

	//data header
	char data_mark[5]; //+1 Byte for zero termination
	fgets(data_mark, 5, file);
	if(!strstr(data_mark, "data"))
	{
		printf("[ERROR] the WAV file is missing the data mark and is therefore not a WAV file\n");
		fclose(file);
		return;
	}

	//data size
	fread(size_of_data, 4, 1, file);

	//data pointer
	*data=malloc(*size_of_data);
	fread(*data, *size_of_data, 1, file);

	fclose(file);
}