#include "philo.h"

#define TAKE_FORK_STR "has taken a fork\n"
#define DROP_FORK_STR "has dropped a fork\n"
#define EAT_STR "is eating \n"
#define THINK_STR "is thinking \n"
#define SLEEP_STR "is sleeping \n"
#define DEAD_STR "is dead \n"

void eat_that_meal(t_philo *philo)
{
    pick_the_fork(philo);
    pthread_mutex_lock(&philo->arg->mutex);
    philo->meals_eat += 1;
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->arg->mutex);
    monitoring(philo, EAT);
    usleep(philo->arg->time_to_eat * 1000);
    drop_the_fork(philo);
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

    // printf("======>%d\n", philo->arg->nbrphilo);
    if(philo->arg->nbrphilo == 1)
    {
        monitoring(philo, FORK);
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
        pthread_mutex_unlock(&philo->arg->mutex);
        eat_that_meal(philo);
        philo_sleeping(philo);
        monitoring(philo, THINK);
    }
    return(NULL);
}

int launch_thread(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
    int i = 0;

        philo->arg->start_time = get_time();
    while(arg->nbrphilo > i)
    {
        if(pthread_create(&philo[i].t_my_enum, NULL, routine, &philo[i]) != 0)
        {
            main_destroy(arg, philo ,forks, FAIL_THREAD);
            return(1);
        }
        i++;
    }
    guard(philo);
    i = 0;
     while(i < philo->arg->nbrphilo)
     {
        if(pthread_join(philo[i].t_my_enum, NULL) != 0)
        {
            main_destroy(arg, philo, forks, JOIN_FAIL);
            return(1);
        }
        i++;
     }
        return(0);
}

void monitoring(t_philo *philos, t_my_enum action_enum)
{
    char *current_action[6] = {DEAD_STR, EAT_STR, THINK_STR,
		SLEEP_STR, TAKE_FORK_STR, DROP_FORK_STR};
    suseconds_t timesta;

    pthread_mutex_lock(&philos->arg->mutex);
    if(philos->arg->the_end)
    {
        pthread_mutex_unlock(&philos->arg->mutex);
        return ;
    }

    timesta = get_time() - philos->arg->start_time;
    // printf("%d\n", philos->nbr_philo1);
    printf("%d %d %s", timesta, philos->nbr_philo1, current_action[action_enum]);
    pthread_mutex_unlock(&philos->arg->mutex);
}