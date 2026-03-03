#include "philo.h"

/*
If there’s an odd number of philosophers and this philosopher has an odd ID, it sleeps a tiny amount before trying to lock. This staggers contention and helps avoid everyone grabbing in perfect sync.
Eso es todo, la coordinación va con los mutex, no tengo que manejarlo
*/

    // routine.c
    // rutina en si
        // last meal ts
        // pequeño sleep para los impares
        // bucle while
            // comer (aqui solo imprime tenedores) + sleep
                // si algo va mal break
            // pensar (con la variable esa a 1 de antes)

long long get_timestamp_ms(t_data *data);
void print_eat(t_data *data, t_philo *philo);

// NOT REALLY BUT LET'S CHECKIN
void	last_meal_checkin(t_philo *philo)
{
    // en caso de que vaya a sobrevivir
	if (philo->ttd > philo->tte + philo->tts)
	{
		pthread_mutex_lock(&philo->m_last_meal);
		philo->last_meal = get_timestamp_ms(philo->data);
		pthread_mutex_unlock(&philo->m_last_meal);
	}
    precise_usleep(philo->tte, philo->data);
    // FIXME: el subject dice que guardemos el momento de EMPEZAR a comer
    // triquiñuela porque previamente ya ha comprobado que va a sobrevivir
	// pthread_mutex_lock(&philo->m_last_meal);
	// philo->last_meal = get_timestamp_ms(philo->data);
	// pthread_mutex_unlock(&philo->m_last_meal);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        print_eat(philo->data, philo);
        last_meal_checkin(philo);
        pthread_mutex_lock(&philo->m_last_meal); 
        philo->meals_eaten++;
        pthread_mutex_lock(&philo->m_last_meal);
        do_sleep(philo);        
    }
    return (NULL);
}

