/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:37:16 by saalarco          #+#    #+#             */
/*   Updated: 2026/02/24 18:56:34 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

// philo_utils.c
void	*ft_memset(void *s, int c, size_t n);

// args_utils.c
int	parse_args(int argc, char const **argv, t_data *data);

// alloc_philos_and_forks.c
int	alloc_philos_and_forks(t_data *data);

int	main(int argc, char const **argv)
{
    t_data data;
    ft_memset(&data, 0, sizeof(t_data));
    if (parse_args(argc, argv, &data))
        return (1);
    if (alloc_philos_and_forks(&data) == 1)
        return (printf("Malloc error\n"), (1));
    // mutex forks
    // mutext writing
    // mutex status (el flag para escribir y tal)

    // distribuye los forks mutexeados a cada philo (previo asigna INFO en cada philo)
        // en cada fillo init mutex last maeal eaten
    // calloc para todos los threads (num filos + 1 para monitor)
        // aqui si que necesito una funcion que limpie TODO (pues ya esta todo el pescado vendido)

    // caso 1 unico philo (buen momento para implementar los mensajes)
    // inicia el timer (esto ya lo tengo)
    // thread create para todos los philos (en su objeto thread alocado previamente)
    // thread create para el monitor
    // pthread join de todos los philos
    // y en este punto claro:  si no esta comiendo o dormido: esta pensando (para esto sirve)
    // pone una variable a 1 en info (es algo as'i como un candado para cualquier nuevo mensaje, si est'a a 1 no escribas mas)
    // pthread join el monitor (de momento va a chequear las muertes)

    // rutina en si
        // last meal ts
        // pequeño sleep para los impares
        // bucle while
            // comer (aqui solo imprime tenedores) + sleep
                // si algo va mal break
            // pensar (con la variable esa a 1 de antes)
    printf("hello world");
    return (0);
}
