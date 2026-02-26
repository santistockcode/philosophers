#ifndef EX02_H
# define EX02_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct			s_philo
{
    int					id;
    pthread_t           threadid;
    struct s_data		*data;
}						t_philo;

typedef struct s_data
{
    long long start_time;
    int         num_philos;
    pthread_mutex_t	write_mutex;
    t_philo     **philos; // array of philosophers
}   t_data;

void precise_usleep(long long us, t_data *data);
long long get_timestamp_ms(t_data *data);
long long ms_from_tv(struct timeval start_time);
void	*worker(void *philo_ptr);

#endif