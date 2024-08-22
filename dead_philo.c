#include "philo.h"

void all_of_them_eat(t_philo *philos)
{
    philos->arg->the_end = true;
    printf("all the philosophers already %d meals\n", philos->arg->time_to_eat);
    pthread_mutex_unlock(&philos->arg->mutex);
}

suseconds_t starv(t_philo *philos)
{
    return((get_current_time() - philos->last_meal) >= philos->arg->time_to_die);
}

bool is_philo_dead(t_philo *philos, int *satisfed_philo)
{
    if(philos->arg->times_each_philosopher_must_eat > 0 && philos->meals_eat >= philos->arg->times_each_philosopher_must_eat)
        *satisfed_philo += 1;
    if(starv(philos))
    {
        pthread_mutex_unlock(&philos->arg->mutex);
        monitoring(philos, DEAD);
        pthread_mutex_lock(&philos->arg->mutex);
        philos->arg->the_end = true;
        pthread_mutex_unlock(&philos->arg->mutex);
        return(true);
    }
    return(false);
}

void guard(t_philo *philos)
{
    int satisfed;
    while (1)
    {
        int i;
        i = 0;
        pthread_mutex_lock(&philos->arg->mutex);
        while(philos->arg->nbrphilo > i)
        {
            if (is_philo_dead(&philos[i], &satisfed))
                return;
            i++;
        }
        if(satisfed == philos->arg->nbrphilo)
            return(all_of_them_eat(philos));
        pthread_mutex_unlock(&philos->arg->mutex);
    }
}
