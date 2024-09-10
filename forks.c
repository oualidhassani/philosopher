/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:30 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/31 16:45:22 by ohassani         ###   ########.fr       */
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

void	skip_spaces(char **av)
{
	int		i;
	char	*start;
	char	*end;

	i = 0;
	while (av[i])
	{
		start = av[i];
		end = av[i];
		while (*start == ' ' || *start == '\t')
			start++;
		end = start;
		while (*end != '\0')
			end++;
		end--;
		while (end > start && (*end == ' ' || *end == '\t'))
			end--;
		*(end + 1) = '\0';
		av[i] = start;
		i++;
	}
}
