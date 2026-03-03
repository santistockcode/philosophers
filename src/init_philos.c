
# include "philo.h"

void destroy_philos(t_data *data)
{
    int index;

    index = 0;
    while (index < data->num_philos)
    {
        pthread_mutex_destroy(&data->philos[index].m_last_meal);
        index++;
    }
}

void destroy_previous_philos(t_data *data, int index)
{
    int i;

    i = 0;
    while (i < index)
    {
        pthread_mutex_destroy(&data->philos[i].m_last_meal);
        i++;
    }
}

int init_philos(t_data *data)
{
    int	index;

    index = 0;
    while (index < data->num_philos)
    {
        (data->philos[index]).id = index + 1;
        (data->philos[index]).ttd = data->ttd;
        (data->philos[index]).tte = data->tte;
        (data->philos[index]).tts = data->tts;
        (data->philos[index]).meals_eaten = 0;
        (data->philos[index]).max_meals = 0;
        (data->philos[index]).data = data;
        if (data->num_meals > 0)
        {
            (data->philos[index]).max_arg = ON;
            (data->philos[index]).max_meals = data->num_meals;
        }
        else
            (data->philos[index]).max_arg = OFF;
        // asigna tenedores
        (data->philos[index]).l_fork = ((data->forks)[index]);
        if (index == data->num_philos - 1)
            (data->philos[index]).r_fork = ((data->forks)[0]);
        else           
            (data->philos[index]).r_fork = ((data->forks)[index + 1]);
        // asigna mutexes
        (data->philos[index]).m_l_fork = &((data->m_forks)[index]);
        if (index == data->num_philos - 1)
            (data->philos[index]).m_r_fork = &((data->m_forks)[0]);
        else
            (data->philos[index]).m_r_fork = &((data->m_forks)[index + 1]);
        if (pthread_mutex_init(&data->philos[index].m_last_meal, NULL))
            return (destroy_previous_philos(data, index), 1);
        index++;
    }
    return (0);
}
