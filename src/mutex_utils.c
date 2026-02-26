# include "philo.h"

void data_mutex_destroy(t_data *data)
{
    int	index;

    index = 0;
    while (index < data->num_philos)
        pthread_mutex_destroy(&data->m_forks[index++]);
    pthread_mutex_destroy(&data->m_write);
    pthread_mutex_destroy(&data->m_status);
}

void    destroy_forks(t_data *data)
{
    int	index;

    index = 0;
    while (index < data->num_philos)
        pthread_mutex_destroy(&data->m_forks[index++]);
}

int data_mutex_init(t_data *data)
{
    int	index;

    index = 0;
    while (index < data->num_philos)
        pthread_mutex_init(&data->m_forks[index++], NULL);
    if (pthread_mutex_init(&data->m_write, NULL))
        return (destroy_forks(data), 1);
    if (pthread_mutex_init(&data->m_status, NULL))
    {
        pthread_mutex_destroy(&data->m_write);
        destroy_forks(data);
        return (1);
    }
    return (0);
}