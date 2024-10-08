/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:05 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/30 21:22:51 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_of_them_eat(t_philo *philos)
{
	philos->arg->the_end = true;
}

bool	starv(t_philo *philo)
{
	return (((get_time() - philo->last_meal) >= philo->arg->time_to_die));
}

bool	is_philo_dead(t_philo *philos, int *satisfed_philo)
{
	if (philos->arg->times_each_philosopher_must_eat > 0
		&& philos->meals_eat > philos->arg->times_each_philosopher_must_eat)
		*satisfed_philo += 1;
	if (starv(philos))
	{
		pthread_mutex_unlock(&philos->arg->mutex);
		monitoring(philos, DEAD);
		pthread_mutex_lock(&philos->arg->mutex);
		philos->arg->the_end = true;
		pthread_mutex_unlock(&philos->arg->mutex);
		return (true);
	}
	return (false);
}

void	*guard(void *philos_void)
{
	t_philo	*philos;
	int		satisfed;
	int		i;

	philos = (t_philo *)philos_void;
	satisfed = 0;
	while (1)
	{
		pthread_mutex_lock(&philos->arg->mutex);
		i = -1;
		while (++i < philos->arg->nbrphilo)
		{
			if (is_philo_dead(&philos[i], &satisfed))
				return (NULL);
		}
		if (satisfed == philos->arg->nbrphilo)
		{
			all_of_them_eat(philos);
			pthread_mutex_unlock(&philos->arg->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philos->arg->mutex);
	}
}
