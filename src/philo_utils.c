/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:59:57 by saalarco          #+#    #+#             */
/*   Updated: 2026/02/24 18:47:55 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*paso;

	paso = (unsigned char *) s;
	count = 0;
	while (count < n)
	{
		*paso++ = (unsigned char) c;
		count++;
	}
	return (s);
}


int	ft_atoi(const char *str)
{
	int	n;
	int	flag;
	int	i;

	n = 0;
	flag = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			flag = -flag;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != 0)
	{
		return (-1);
	}
	return (n * flag);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			cntr;
	unsigned char	*pntr;

	cntr = 0;
	pntr = s;
	if (n <= 0)
		return ;
	while (cntr < n)
	{
		pntr[cntr] = 0;
		cntr++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, count * size);
	return (ptr);
}