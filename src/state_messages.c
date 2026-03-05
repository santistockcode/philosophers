
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
    printf("%lld \t%d \tdied\n", get_timestamp_ms(data), philo->id);
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
    printf("%lld \t%d \tis sleeping\n", get_timestamp_ms(data), philo->id);
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
    printf("%lld \t%d \tis eating\n", get_timestamp_ms(data), philo->id);
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
    printf("%lld \t%d \thas taken a fork\n", get_timestamp_ms(data), philo->id);
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
    printf("%lld \t%d \tis thinking\n", get_timestamp_ms(data), philo->id);
    pthread_mutex_unlock(&data->m_write);
}