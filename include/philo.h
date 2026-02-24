#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>

# include <stdbool.h>
# include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int id;
    long long ttd;
    long long tte;
    long long tts;
    pthread_mutex_t *m_l_fork;
    unsigned char l_fork;
    pthread_mutex_t *m_r_fork;
    unsigned char r_fork;
    t_data *data;
}   t_philo;

typedef struct s_data
{
    int num_philos;
    long long start_time;
    long long ttd;
    long long tte;
    long long tts;
    int num_meals;
    pthread_mutex_t *m_forks;
    unsigned char *forks;
    pthread_mutex_t m_write;
    pthread_t *threads;
    t_philo *philos;
    unsigned char quiet_flag;
}   t_data;

#endif