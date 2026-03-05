#include "philo.h"

// la flag de coger y descoger el tenedor está controlada por m_left o m_right respectivamente

void	last_meal_checkin(t_philo *philo)
{
	if (philo->ttd > philo->tte + philo->tts)
	{
		pthread_mutex_lock(&philo->m_last_meal);
		philo->last_meal = get_timestamp_ms(philo->data);
		pthread_mutex_unlock(&philo->m_last_meal);
	}
    precise_usleep(philo->tte, philo->data);
    // FIXME: el subject dice que guardemos el momento de EMPEZAR a comer
    // "si un filósofo no empieza a comer en time_to_die milisegundos desde que comenzó su ultima comida"
	// pthread_mutex_lock(&philo->m_last_meal);
	// philo->last_meal = get_timestamp_ms(philo->data);
	// pthread_mutex_unlock(&philo->m_last_meal);
}

// COMPROBAR TENEDORES y lockearlos
    // pequeño delay para los impares
    // si estoy en mute devuelvo 1 porque salf
    // en todo caso pequeño usleep para dar tiempo a coger tenedores
    // flag a ON (tengo un tenedor)
    // imprimir tenedor




int do_eat(t_philo *philo)
{
    // COMPROBAR TENEDORES y lockearlos
    // si hemos llegado hasta aquí imprimir que comemos
    // updatear last_meal
    // soltar tenedores (la flag esa)
    // si de verdad hemos comido (no se ha interrumpido el sleep)
        // actualizamos las veces que hemos comido
    // comprobamos de nuevo si ya hemos comido lo suficiente
    // devolvemos 1 si no hemos comido, 0 si sí hemos comido
    print_eat(philo->data, philo);
    last_meal_checkin(philo);
    pthread_mutex_lock(&philo->m_last_meal); 
    philo->meals_eaten++;
    pthread_mutex_lock(&philo->m_last_meal);
    return (0);    
}
