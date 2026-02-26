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

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1)
    {
        printf("%lld %d \tsimplemente existe\n", get_timestamp_ms(philo->data), philo->id);
        do_sleep(philo);
    }
    return (NULL);
}

