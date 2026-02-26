# include "ex02.h"

void precise_usleep(long long us, t_data *data);

void	prin_tstr(long long ts, int id, char *str)
{
	printf("[%lld] %d: %s\n", ts, id, str);
}

void	*worker(void *philo_ptr)
{
    t_data *data;

    t_philo *philo = (t_philo *)philo_ptr;
    data = philo->data;
    pthread_mutex_lock(&(data->write_mutex));
    prin_tstr(get_timestamp_ms(data), philo->id, "start");
    precise_usleep(500, data);
    prin_tstr(get_timestamp_ms(data), philo->id, "end");
    pthread_mutex_unlock(&(data->write_mutex));
    return (NULL);
}