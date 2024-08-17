#include "philo.h"

#define EAT "is eating"
#define SLEEP "is eating"
#define THINK "is thinking"
#define DEAD "is dead"

void launch_thread(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
    int i = 0;

    while(philo->nbr_philo )
}
void monitoring(t_arg *arg, t_philo *philos, pthread_mutex_t *forks)
{
    char *current_action[4] = {EAT, SLEEP, THINK, DEAD};


    pthread_mutex_lock(&arg->mutex);
    if(arg->the_end)
    {
        pthread_mutex_unlock(&arg->mutex);
        return ;
    }

    time = 
}