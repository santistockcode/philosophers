
#include "philo.h"

void print_someone_died(t_data* data, t_philo* philo)
{
    pthread_mutex_lock(&data->m_write);
    if (data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    data->mute = ON;
    printf("%lld %d died\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}


void print_sleep(t_data* data, t_philo *philo)
{
    pthread_mutex_lock(&data->m_write);
    if (data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    printf("%lld %d is sleeping\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}

void print_eat(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->m_write);
    if(data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    printf("%lld %d is eating\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}

void    print_fork(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->m_write);
    if(data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    printf("%lld %d has taken a fork\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}

void    print_think(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->m_write);
    if(data->mute == ON)
    {
        pthread_mutex_unlock(&data->m_write);
        return ;
    }
    printf("%lld %d is thinking\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}

// void    print_release_fork(t_data *data, t_philo *philo)
// {
//     pthread_mutex_lock(&data->m_write);
//     if(data->mute == ON)
//     {
//         pthread_mutex_unlock(&data->m_write);
//         return ;
//     }
//     printf("%lld %d has suelta fork\n", get_timestamp_ms(data), philo->id);
//     pthread_mutex_unlock(&data->m_write);
// }