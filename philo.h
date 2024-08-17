#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define INIT_MUTEX "fail the mutex initialization"

// struct of agrs
typedef struct s_arg
{
    int     nbrphilo;
    int     time_to_die;
    int     time_to_eat;
    int     time_sleep;
    int     times_each_philosopher_must_eat;
    pthread_mutex_t     mutex;
    bool    the_end;
} t_arg;

/// sturct of philos
typedef struct s_philo
{
    int         nbr_philo1;
    suseconds_t         time;
    pthread_mutex_t     *left;
    pthread_mutex_t     *right;
    suseconds_t     start_time;
} t_philo;

// struct of enum
typedef enum e_my_enum
{
    EAT,
    THINK,
    SLEEP,
    DEAD,
    FORK,

}   t_my_enum;

//parsing
void    parsing(int ac, char **av);

// init 
pthread_mutex_t     *init_forks(t_arg *arg);
void                init_arg(t_arg *arg, char **av);
t_philo     *init_philo(t_arg *arg, pthread_mutex_t *the_forks);

// utils
int	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void    free_forks(pthread_mutex_t *forks, int until);

// destroy
int	main_destroy(t_arg *arg, t_philo *philo, pthread_mutex_t *forks, char *error_msg);


#endif