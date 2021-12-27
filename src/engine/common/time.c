#include <time.h>


long tt_time_current_ns()
{
	long time_out=0;
	struct timespec ts;
	if(TIME_UTC==timespec_get(&ts, TIME_UTC))
	{
		time_out=ts.tv_sec*1000000000;
		time_out+=ts.tv_nsec;
	}
	return time_out;
}