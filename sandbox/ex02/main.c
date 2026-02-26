
#include "ex02.h"

void	*worker(void *philo_ptr);


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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
	return (n * flag);
}

int init_data(t_data **data, int num_philos)
{
    struct timeval tv;
    int ret_gtod;
    long long now;

    ret_gtod = gettimeofday(&tv, NULL);
    if (ret_gtod < 0)
        return (-1);
    now = ms_from_tv(tv);
    *data = (t_data *)malloc(sizeof(t_data *));
    if (!(*data))
        return (printf("malloc error"), -1);
    (*data)->start_time = now;
	(*data)->philos = (t_philo **)malloc(sizeof(t_philo *) * num_philos);
	if (!(*data)->philos)
		return (free(*data), printf("malloc error philos"), -1);
    return (0);
}



// receives number of philosophers
int main(int argc, char **argv)
{
	t_data *data;
	int num_philos;
	int i;

	i = 0;
	if (argc != 2)
		return (printf("Usage: ./philo number_of_philosophers\n"), 1);
	if (ft_atoi(argv[1]) <= 0)
		return (printf("Error: number_of_philosophers must be a positive integer\n"), 1);
	num_philos = ft_atoi(argv[1]);
	if (init_data(&data, num_philos) != 0)
        return (1);
	data->num_philos = num_philos;
	if (data->num_philos == 1)
	{
		printf("0\tphilosopher [1]:  \thas taken a fork\n");
		printf("X\tphilosopher [1]:  \thas died\n");
		return (1);
	}
	pthread_mutex_init(&(data->write_mutex), NULL);
	while(++i <= num_philos)
	{
		data->philos[i - 1]->id = i;
		pthread_create(&data->philos[i - 1]->threadid, NULL, (void *)worker, (void *)data->philos[i - 1]);
		precise_usleep(1, data);
	}
	i = 0;
	while (++i <= num_philos)
		pthread_join(data->philos[i - 1]->threadid, NULL);
	// destroy and free data
	pthread_mutex_destroy(&(data->write_mutex));
	free(data->philos);
	free(data);
	return (0);
}