
#include "philo.h"

void print_sleep(t_data* data, t_philo *philo)
{
    pthread_mutex_lock(&data->m_write);
    if (data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    printf("%lld \t%d \tis sleeping\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}