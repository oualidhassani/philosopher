/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:30 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/29 09:31:44 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
}
