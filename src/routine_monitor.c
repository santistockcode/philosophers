
#include "philo.h"

// atajo de circuito o como se llame si yo ya he matado a cada philo que ha comido lo que tenía que comer
int is_philo_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	// momento actual - ultima comida (cuando terminó) 
	if (get_timestamp_ms(philo->data) - philo->last_meal >
		philo->ttd)
	{
		pthread_mutex_unlock(&philo->m_last_meal);
		// aquí devolvemos 1 porque lo que hay que chequear es que todos hayan comido al menos X veces (para esto se usa el mute)
		if (philo->max_arg == ON && philo->meals_eaten >= philo->max_meals)
			return (1);
		pthread_mutex_lock(&data->m_status);
		data->status = ON;
		pthread_mutex_unlock(&data->m_status);
		print_someone_died(data, philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->m_last_meal);
	return (1);
}

int	check_end(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->num_philos)
	{
		if (is_philo_dead(data, &philos[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// int check_dead()

// TODO: si me da problemas puedo chequear alternativamente si mueren o si han comido
void *routine_monitor(void *arg)
{
	t_data *data = (t_data *) arg;

	while (1)
	{
		if (check_end(data, data->philos))
			break ;
		// TODO: LOS FILÓSOFOS SI HAN TERMINADO DE COMER, autonomamente se mueren, por lo que en create_threads_and_join.c 
		// se pondra mute en ON
		// TODO: chequear si mute de data está ON y si lo está es que todo quisqui ha comido y puedo salir
	}
	return (NULL);
}