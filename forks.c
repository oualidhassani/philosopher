#include "philo.h"

 void	pick_the_fork(t_philo *philo)
{
	if (philo->nbr_philo1 % 2 == 0)
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

 void	drop_the_fork(t_philo *philo)
{
	if (philo->nbr_philo1 % 2 == 0)
	{
		pthread_mutex_unlock(philo->left);
		monitoring(philo, DROP);
		pthread_mutex_unlock(philo->right);
		monitoring(philo, DROP);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		monitoring(philo, DROP);
		pthread_mutex_unlock(philo->left);
		monitoring(philo, DROP);
	}
}