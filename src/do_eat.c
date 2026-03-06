#include "philo.h"

// la flag de coger y descoger el tenedor está controlada por m_left o m_right respectivamente

void	meal_clock_in(t_philo *philo)
{
    // si va a sobrevivir sea par o impar
	// if (philo->ttd > philo->tte + philo->tts)
	// {
    pthread_mutex_lock(&philo->m_last_meal);
    philo->last_meal = get_timestamp_ms(philo->data);
    pthread_mutex_unlock(&philo->m_last_meal);
	// }
    precise_usleep(philo->tte, philo->data);
    // FIXME: el subject dice que guardemos el momento de EMPEZAR a comer
    // "si un filósofo no empieza a comer en time_to_die milisegundos desde que comenzó su ultima comida"
	// pthread_mutex_lock(&philo->m_last_meal);
	// philo->last_meal = get_timestamp_ms(philo->data);
	// pthread_mutex_unlock(&philo->m_last_meal);
}

// la primera vez va a esperar para comer, no? 
// COMPROBAR TENEDORES y lockearlos
    // pequeño delay para los impares
    // si estoy en mute devuelvo 1 porque salf
    // en todo caso pequeño usleep para dar tiempo a coger tenedores
    // flag a ON (tengo un tenedor)
    // imprimir tenedor
// tenedores a 0 hasta que se usan
// cuando se usan se pasan a 1
// cuando se sueltan se pasan a 0 de nuevo

int take_fork(t_philo *philo)
{
    pthread_mutex_t *m_fork[2];
    t_bool *p_fork[2];

    // en caso de ser par chequeamos primero el izquierdo luego el derecho
    if (philo->id % 2 == 0)
    {
        m_fork[0] = philo->m_l_fork;
        p_fork[0] = &philo->l_fork;
        m_fork[1] = philo->m_r_fork;
        p_fork[1] = &philo->r_fork;
    }
    else    // si el id es impar al revés
    {
        m_fork[0] = philo->m_r_fork;
        p_fork[0] = &philo->r_fork;
        m_fork[1] = philo->m_l_fork;
        p_fork[1] = &philo->l_fork;
    }
    // TRY FORK [0]
    // ÑAPA: si son impares y es un philo impar
    if (philo->data->num_philos % 2 == 1 && philo->id % 2 != 0)
        usleep(50);
    pthread_mutex_lock(m_fork[0]);
    while(*p_fork[0] != OFF) // hasta que esté por primera vez disponible
    {
        pthread_mutex_unlock(m_fork[0]);
        pthread_mutex_lock(&philo->data->m_write);
        if (philo->data->mute == ON)
        {
            pthread_mutex_unlock(&philo->data->m_write);
            return (1);
        }
        pthread_mutex_unlock(&philo->data->m_write);
        precise_usleep(10, philo->data); // TODO: protect
        pthread_mutex_lock(m_fork[0]);
    }
    *p_fork[0] = ON; // we take the fucking fork 0
    pthread_mutex_unlock(m_fork[0]);
    print_fork(philo->data, philo);
    // TRY FORK [1]
    if (philo->data->num_philos % 2 == 1 && philo->id % 2 != 0)
        usleep(50);
    pthread_mutex_lock(m_fork[1]);
    while(*p_fork[1] != OFF) // hasta que esté por primera vez disponible
    {
        pthread_mutex_unlock(m_fork[1]);
        pthread_mutex_lock(&philo->data->m_write);
        if (philo->data->mute == ON)
        {
            pthread_mutex_unlock(&philo->data->m_write);
            return (1);
        }
        pthread_mutex_unlock(&philo->data->m_write);
        precise_usleep(10, philo->data); // TODO: protect
        pthread_mutex_lock(m_fork[1]);
    }
    *p_fork[1] = ON; // we take the fucking fork 1
    pthread_mutex_unlock(m_fork[1]);
    print_fork(philo->data, philo);
    return (0);
}

static void	release_fork(t_philo *philo)
{
    pthread_mutex_t *m_fork[2];
    t_bool *p_fork[2];

    // soltamos también en orden
    if (philo->id % 2 == 0)
    {
        m_fork[0] = philo->m_l_fork;
        p_fork[0] = &philo->l_fork;
        m_fork[1] = philo->m_r_fork;
        p_fork[1] = &philo->r_fork;
    }
    else
    {
        m_fork[0] = philo->m_r_fork;
        p_fork[0] = &philo->r_fork;
        m_fork[1] = philo->m_l_fork;
        p_fork[1] = &philo->l_fork;
    }
	pthread_mutex_lock(m_fork[0]);
	*p_fork[0] = OFF;
	pthread_mutex_unlock(m_fork[0]);
    pthread_mutex_lock(m_fork[1]);
	*p_fork[1] = OFF;
	pthread_mutex_unlock(m_fork[1]);
}

// si do_eat devuelve 1 es para decirle a la rutina: hasta aquí hemos llegado, mátame camión.
int do_eat(t_philo *philo)
{
    // COMPROBAR TENEDORES y lockearlos
    // si hemos llegado hasta aquí imprimir que comemos, si no devolver 1
    // updatear last_meal
    // soltar tenedores (la flag esa)
    // si de verdad hemos comido (no se ha interrumpido el sleep)
        // actualizamos las veces que hemos comido
    // comprobamos de nuevo si ya hemos comido lo suficiente
    // devolvemos 1 si no hemos comido, 0 si sí hemos comido
    if (take_fork(philo) == 1)
        return (1);
    print_eat(philo->data, philo);
    meal_clock_in(philo);
    release_fork(philo);
    pthread_mutex_lock(&philo->m_last_meal); 
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->m_last_meal);
    if (philo->max_arg == ON && philo->meals_eaten >= philo->max_meals)
        return (1);
    return (0);    
}
