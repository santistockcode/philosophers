
# include "philo.h"

void print_sleep(t_data* data, t_philo *philo);

t_bool	do_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->m_status);
    if (philo->data->status == ON)
    {
        pthread_mutex_unlock(&philo->data->m_status);
        return (ON);
    }
    pthread_mutex_unlock(&philo->data->m_status);
    print_sleep(philo->data, philo);
    return (precise_usleep(philo->tts, philo->data), OFF);
}