# include "ex02.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

long long ms_from_tv(struct timeval start_time)
{
    return ((long long)(start_time.tv_sec * 1000) + (long long)(start_time.tv_usec / 1000));
}

long long get_timestamp_ms(t_data *data)
{
	struct timeval tv;
    int ret_gtod;
    long long now;

    ret_gtod = gettimeofday(&tv, NULL);
    if (ret_gtod < 0)
        return (-1);
    now = ms_from_tv(tv);
	return (now - data->start_time);
}

void precise_usleep(long long us, t_data *data)
{
	long long now;
	long long later;

	now = get_timestamp_ms(data);
	while(1)
	{
		usleep(100);
		later = get_timestamp_ms(data);		
		if ((later - now) > us)
				break;
		}
}

	
