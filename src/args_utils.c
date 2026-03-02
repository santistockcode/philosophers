/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:31:55 by saalarco          #+#    #+#             */
/*   Updated: 2026/02/24 18:49:45 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	ft_atoi(const char *str);

int	parse_args(int argc, char const **argv, t_data *data)
{
	if (!data || argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), (1));
	data->num_philos = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_meals = ft_atoi(argv[5]);
		if (data->num_meals == 0)
			return (printf("Invalid arguments\n"), (1));
	}
	else
		data->num_meals = 0;
	if (data->num_philos <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0 || data->num_meals < 0)
		return (printf("Invalid arguments\n"), (1));
	return (0);
}