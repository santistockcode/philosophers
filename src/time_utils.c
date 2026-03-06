
#include "philo.h"

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
/*
t_bool	ph_usleep(t_info *info, size_t time)
{
	size_t	start_time;

	start_time = ph_get_time();
	while (ph_get_time() < start_time + time)
	{
		pthread_mutex_lock(&info->m_status);
		if (info->status == FALSE)
		{
			pthread_mutex_unlock(&info->m_status);
			return (FALSE);
		}
		pthread_mutex_unlock(&info->m_status);
		usleep(50);
	}
	return (TRUE);
}
FIXME: the idea to do it boolean is to avoid yet another mutex upstairs
also
FIXME: reality is that we want to add times eaten ONCE sleep is finished, if it doesn't finish
the philo didn't really ate, maybe they just started and we would be counting it wrong. 
*/
int precise_usleep(long long us, t_data *data)
{
	long long now;
	long long later;

	now = get_timestamp_ms(data);
	while(1)
	{
		pthread_mutex_lock(&data->m_status);
		if (data->status == ON)
		{
			pthread_mutex_unlock(&data->m_status);
			return (1);
		}
		pthread_mutex_unlock(&data->m_status);
		usleep(50);
		later = get_timestamp_ms(data);		
		if ((later - now) >= us)
				break;
	}
	return (0);
}
