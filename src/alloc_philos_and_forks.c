/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_philos_and_forks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:03:23 by saalarco          #+#    #+#             */
/*   Updated: 2026/02/24 19:03:24 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*ft_calloc(size_t count, size_t size);

int	alloc_philos_and_forks(t_data *data)
{
	data->forks = (unsigned char *) ft_calloc(data->num_philos, sizeof(unsigned char *));
	if (data->forks == NULL)
		return (1);
	data->m_forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	if (data->m_forks == NULL)
	{
		free(data->forks);
		return (1);
	}
	data->philos = ft_calloc(data->num_philos, sizeof(t_philo));
	if (data->philos == NULL)
	{
		free(data->forks);
		free(data->m_forks);
		return (1);
	}
	return (0);
}
