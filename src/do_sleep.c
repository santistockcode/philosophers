
# include "philo.h"

void print_sleep(t_data* data, t_philo *philo);

t_bool	do_sleep(t_philo *philo)
{
    // NO MONITOR FOR NOW
    // pthread_mutex_lock(&philo->data->m_status);
    // if (philo->data->status == FALSE)
    // {
    //     pthread_mutex_unlock(&philo->data->m_status);
    //     return (FALSE);
    // }
    // pthread_mutex_unlock(&philo->data->m_status);
    print_sleep(philo->data, philo);
    return (precise_usleep(philo->tts, philo->data), OFF);
}