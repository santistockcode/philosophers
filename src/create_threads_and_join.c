
# include "philo.h"

// routine.c
void *routine(void *arg);

// create_threads_and_join.c
// caso 1 unico philo (buen momento para implementar los mensajes)
// inicia el timer (esto ya lo tengo)
// thread create para todos los philos (en su objeto thread alocado previamente)
// thread create para el monitor
// pthread join de todos los philos
// pone mute a 1 en info para que el monitor "salga"
// pthread join el monitor

static void handle_single_philo(t_data *data)
{
    printf("0\t%d has taken a fork\n", 1);
    usleep(data->ttd * 1000);
    printf("%lld\t%d died\n", data->ttd, 1);
}

void create_threads_and_join(t_data *data)
{
    int index;

    if (data->num_philos == 1)
    {
        handle_single_philo(data);
        return ;
    }
    index = 0;
    while (index < data->num_philos)
    {
        pthread_create(&data->threads[index], NULL, routine, &data->philos[index]);
        index++;
    }
    // pthread_create(&data->threads[index], NULL, monitor_routine, data);
    index = 0;
    while (index < data->num_philos)
    {
        pthread_join(data->threads[index], NULL);
        index++;
    }
    // data->status = 1;
    // pthread_join(data->threads[index], NULL);
}