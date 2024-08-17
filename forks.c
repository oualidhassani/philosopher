#include "philo.h"

void pick_the_fork(t_philo *philo)
{
    if(philo->arg->nbrphilo % 2 == 0)
    {
        pthread_mutex_lock(philo->left);
        monitoring(philo, FORK);
        pthread_mutex_lock(philo->right);
        monitoring(philo, FORK);
    }
    else
    {
        pthread_mutex_lock(philo->right);
        monitoring(philo, FORK);
        pthread_mutex_lock(philo->left);
        monitoring(philo, FORK);
    }
}

void drop_the_fork(t_philo *philo)
{
        if(philo->arg->nbrphilo % 2 == 0)
    {
        pthread_mutex_unlock(philo->left);
        monitoring(philo, FORK);
        pthread_mutex_unlock(philo->right);
        monitoring(philo, FORK);
    }
    else
    {
        pthread_mutex_unlock(philo->right);
        monitoring(philo, FORK);
        pthread_mutex_unlock(philo->left);
        monitoring(philo, FORK);
    }
}