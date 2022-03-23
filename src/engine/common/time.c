#include <tt.h>
#include <time.h>


long time_last_frame_ns=0;
long time_new_frame_ns=0;
long time_delta_frame_ns=0;
float time_delta_frame_s=0;

void tt_time_init() //initialize the last frame value because of UNIX time and so on
{
	time_last_frame_ns=tt_time_current_ns();
}

void tt_time_update()
{
	time_new_frame_ns=tt_time_current_ns();
	time_delta_frame_ns=time_new_frame_ns - time_last_frame_ns;
	time_delta_frame_s=(float)time_delta_frame_ns/1000000000;
	time_last_frame_ns=time_new_frame_ns;
}


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

long tt_time_current_frame_ns()
{
	return time_delta_frame_ns;
}

float tt_time_current_frame_s()
{
	return time_delta_frame_s;
}