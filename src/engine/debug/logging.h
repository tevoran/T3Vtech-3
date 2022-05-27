#ifndef TT_DEBUG_LOGGING_H
#define TT_DEBUG_LOGGING_H

#include <tt.h>

enum tt_log_type{TT_INFO, TT_WARN, TT_ERROR};

struct tt_log_file
{
	const char *location;
	FILE *file;
};

void tt_log_open_log_file(const char *file_location);
void tt_log(enum tt_log_type type, const char *format, ...);
void tt_log_s(enum tt_log_type type, const char *string);

#endif /* TT_DEBUG_LOGGING_H */