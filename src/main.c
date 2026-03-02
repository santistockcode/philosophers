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

// alloc_utils.c
int	alloc_philos_and_forks(t_data *data);
void free_philos_and_forks(t_data *data);
int alloc_threads(t_data *data);
void free_threads(t_data *data);

// mutex_utils.c
int data_mutex_init(t_data *data);
void data_mutex_destroy(t_data *data);

// init_philos.c
int init_philos(t_data *data);
void destroy_philos(t_data *data);

int	main(int argc, char const **argv)
{
    t_data data;
    ft_memset(&data, 0, sizeof(t_data));
    if (parse_args(argc, argv, &data))
        return (1);
    if (alloc_philos_and_forks(&data) == 1)
        return (printf("Malloc error\n"), (1));
    if (data_mutex_init(&data))
        return (printf("Mutex init error\n"), free_philos_and_forks(&data), 1);
    if (init_philos(&data))
        return (printf("Philos init error\n"),  data_mutex_destroy(&data), free_philos_and_forks(&data), 1);
    // TODO: refactor este return en una función en alloc utils
    if (alloc_threads(&data))
        return (printf("Malloc error\n"), destroy_philos(&data), data_mutex_destroy(&data), free_philos_and_forks(&data), 1);

    create_threads_and_join(&data);

    // TODO: refactor este return en una función en alloc utils
    return (free_threads(&data), destroy_philos(&data), data_mutex_destroy(&data), free_philos_and_forks(&data), 0);
}
