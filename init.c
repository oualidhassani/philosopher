#include "philo.h"

t_philo    *init_philo(t_arg *arg, pthread_mutex_t *the_forks)
{
    t_philo *philo;

    philo = malloc(arg->nbrphilo *sizeof(pthread_mutex_t));

    int i  = 0;

    while(i < arg->nbrphilo)
    {
        philo[i].nbr_philo1 = i + 1;
        philo[i].left = &the_forks[i];
        philo[i].right = &the_forks[i] + 1;
        // philo[i].time = time();
        i++;
    }

    return(philo);
}
void    init_arg(t_arg *arg, char **av) 
{
    arg->nbrphilo = ft_atoi(av[1]);
    arg->time_to_die = ft_atoi(av[2]);
    arg->time_to_eat = ft_atoi(av[3]);
    arg->time_sleep = ft_atoi(av[4]);
    arg->times_each_philosopher_must_eat = -1;

    if(av[5])
        arg->times_each_philosopher_must_eat = ft_atoi(av[5]);

    if(arg->nbrphilo == 0 || arg->time_to_die == 0 || arg->time_sleep == 0 || arg->time_to_eat == 0)
        ft_putstr_fd("Error\n", 2);

    if(pthread_mutex_init(&arg->mutex, NULL) != 0)
    {
        main_destroy(0, NULL, NULL, INIT_MUTEX);
        return ;
    }
    arg->the_end = false;
}

pthread_mutex_t *init_forks(t_arg *arg)
{
    pthread_mutex_t *fork;

    fork = malloc(arg->nbrphilo * sizeof(pthread_mutex_t));

    int i  = 0;
    // if(!fork)

    while(arg->nbrphilo > i)
    {
        if(pthread_mutex_init(&fork[i], NULL) != 0)
            free_forks(fork, i);
        i++;
    }
    return(fork);
}

long long int get_current_time()
{
    struct timeval time;

    gettimeofday(&time,NULL);
    return ((time.tv_sec / 1000) + (time.tv_usec * 1000));
}
