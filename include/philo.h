#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>

# include <sys/time.h>

# include <stdbool.h>
# include <pthread.h>

typedef struct s_data t_data;
typedef unsigned char	t_bool;
# define OFF 0
# define ON 1

typedef struct s_philo
{
    int id;
    long long ttd;
    long long tte;
    long long tts;
    int num_meals;
    // last meal time stamp (when it STARTED eating)
    pthread_mutex_t m_last_meal;
    long long last_meal;
    // left/ritght fork
    pthread_mutex_t *m_l_fork;
    t_bool l_fork;
    pthread_mutex_t *m_r_fork;
    t_bool r_fork;
    // data
    t_data *data;
}   t_philo;

typedef struct s_data
{
    int num_philos;
    long long start_time;
    long long ttd;
    long long tte;
    long long tts;
    int num_meals; // not specified in subject, I I've decided that is gonna be 1 or more, else is invalid
    // forks
    pthread_mutex_t *m_forks;
    t_bool *forks;
    // writing
    pthread_mutex_t m_write;
    t_bool mute; // if someone dies mute turns to 1 (luego está en los utils de mensajes)
    // death check
    pthread_mutex_t		m_status; // wrapper for status
	t_bool		status; // coordinates monitor (someone died?) with usleep (don't start sleeping if someone died)
    // philos
    pthread_t *threads;
    t_philo *philos;
}   t_data;

// main create threads and join orquestrator
void create_threads_and_join(t_data *data);

// roles
t_bool	do_sleep(t_philo *philo);

// time_utils.c
long long get_timestamp_ms(t_data *data);
void precise_usleep(long long us, t_data *data);

#endif