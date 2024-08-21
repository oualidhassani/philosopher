#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define INIT_MUTEX "fail the mutex initialization"
#define FAIL_THREAD "fail the creation of the thread"
#define JOIN_FAIL "fail the join"

#define MICRO_SEC 1000
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
    int     meals_eat;
    suseconds_t     start_time;
    suseconds_t     last_meal;
    pthread_t       t_my_enum;
    t_arg       *arg;
} t_philo;

// struct of enum
typedef enum e_my_enum
{
    EAT,
    THINK,
    SLEEP,
    DEAD,
    FORK,
    DROP,

}   t_my_enum;

//parsing
void    parsing(int ac, char **av);

// init 
pthread_mutex_t     *init_forks(t_arg *arg);
bool    init_arg(t_arg *arg, char **av) ;
t_philo     *init_philo(t_arg *arg, pthread_mutex_t *the_forks);

// utils
int	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void    free_forks(pthread_mutex_t *forks, int until);

// destroy
int	main_destroy(t_arg *arg, t_philo *philo, pthread_mutex_t *forks, char *error_msg);

// create the thread
int     launch_thread(t_arg *arg, t_philo *philo, pthread_mutex_t *forks);
void monitoring(t_philo *philos, t_my_enum action_enum);

// get the time
suseconds_t get_current_time();

// the forks
void pick_the_fork(t_philo *philo);
void drop_the_fork(t_philo *philo);
void eat_that_meal(t_philo *philo);
void philo_sleeping(t_philo *philo);

// the dead of the philos 
suseconds_t starv(t_philo *philos);
void guard(t_philo *philos);

#endif