#include "philo.h"

#define EAT EAT
#define SLEEP SLEEP
#define THINK THINK
#define DEAD DEAD
#define TAKE_FORK TAKE_FORK

void eat_that_meal(t_philo *philo)
{
    pick_the_fork(philo);
    pthread_mutex_lock(&philo->arg->mutex);
    philo->meals_eat += 1;
    philo->last_meal = get_current_time();
    pthread_mutex_unlock(&philo->arg->mutex);
    monitoring(philo, EAT);
    usleep(philo->arg->time_to_eat * 1000);
}

void philo_sleeping(t_philo *philo)
{
    monitoring(philo, SLEEP);
    usleep(philo->arg->time_sleep * 1000);
}

void *routine(void *_philo)
{
    
    t_philo *philo;
    philo = (t_philo *)_philo;

    if(philo->arg->nbrphilo == 1)
    {
        monitoring(philo, TAKE_FORK);
        return(NULL);
    }
    while(1)
    {
        pthread_mutex_lock(&philo->arg->mutex);
        if(philo->arg->the_end)
        {
            pthread_mutex_unlock(&philo->arg->mutex);
            break;
        }
        eat_that_meal(philo);
        philo_sleeping(philo);
        monitoring(philo, THINK);
    }
    return(NULL);
}

int launch_thread(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
    int i = 0;

    while(arg->nbrphilo > i)
    {
        philo[i].start_time = get_current_time();
        if(pthread_create(&philo[i].t_my_enum, NULL, routine, &philo[i]) != 0)
        {
            main_destroy(arg, philo ,forks, FAIL_THREAD);
            return(0);
        }
        i++;
    }
    return(1);
}


void monitoring(t_philo *philos, t_my_enum action_enum)
{
    char *current_action[5] = {"is eating", "is sleeping", "is thinking", "is dead", "take the fork"};

    suseconds_t timesta;

    pthread_mutex_lock(&philos->arg->mutex);
    if(philos->arg->the_end)
    {
        pthread_mutex_unlock(&philos->arg->mutex);
        return ;
    }
    pthread_mutex_unlock(&philos->arg->mutex);

    timesta = get_current_time() - philos->start_time;
    printf("%d %d %s", timesta, philos->nbr_philo1, current_action[action_enum]);
}