#include <tt.h>

struct tt_log_file tt_log_file;

void tt_log_open_log_file(const char *file_location)
{
	if(file_location==NULL)
	{
		printf("[ERROR] no logging file specified");
		return;
	}

	tt_log_file.location=file_location;
	tt_log_file.file=fopen(tt_log_file.location, "w");
	if(tt_log_file.file==NULL)
	{
		printf("[ERROR] couldn't create logging file at %s\n", tt_log_file.location);
	}
	fclose(tt_log_file.file);
}

void tt_log(enum tt_log_type type, const char *format, ...)
{
	tt_log_file.file=fopen(tt_log_file.location, "a+");
	if(tt_log_file.file==NULL)
	{
		printf("[ERROR] couldn't open logging file at %s\n", tt_log_file.location);
		fclose(tt_log_file.file);
		return;
	}

	va_list args;
	va_start(args, format);
	if(type==TT_INFO)
	{
		fprintf(tt_log_file.file, "[INFO] ");
	}
	if(type==TT_WARN)
	{
		fprintf(tt_log_file.file, "[WARNING] ");
	}
	if(type==TT_ERROR)
	{
		fprintf(tt_log_file.file, "[ERROR] ");
	}
	vfprintf(tt_log_file.file, format, args);
	fprintf(tt_log_file.file, "\n");

	va_end(args);
	fclose(tt_log_file.file);
}

void tt_log_s(enum tt_log_type type, const char *string)
{
	tt_log(type, "%s", string);
}