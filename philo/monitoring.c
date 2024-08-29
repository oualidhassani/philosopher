/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:57 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/29 09:31:59 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define TAKE_FORK_STR "has taken a fork\n"
#define EAT_STR "is eating \n"
#define THINK_STR "is thinking \n"
#define SLEEP_STR "is sleeping \n"
#define DEAD_STR "is dead \n"

void	eat_that_meal(t_philo *philo)
{
	pick_the_fork(philo);
	pthread_mutex_lock(&philo->arg->mutex);
	philo->meals_eat += 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->arg->mutex);
	monitoring(philo, EAT);
	ft_usleep(philo->arg->time_to_eat);
	drop_the_fork(philo);
}

void	philo_sleeping(t_philo *philo)
{
	monitoring(philo, SLEEP);
	ft_usleep(philo->arg->time_sleep);
}

void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->arg->nbrphilo == 1)
	{
		monitoring(philo, FORK);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->arg->mutex);
		if (philo->arg->the_end)
		{
			pthread_mutex_unlock(&philo->arg->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->mutex);
		eat_that_meal(philo);
		philo_sleeping(philo);
		monitoring(philo, THINK);
		ft_usleep(5);
	}
	return (NULL);
}

int	launch_thread(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
	int			i;

	i = -1;
	philo->arg->start_time = get_time();
	while (arg->nbrphilo > ++i)
	{
		if (pthread_create(&philo[i].t_my_enum, NULL, routine, &philo[i]) != 0)
		{
			main_destroy(arg, philo, forks, FAIL_THREAD);
			return (1);
		}
	}
	if (create_and_join_guard_thread(arg, philo, forks) != 0)
		return (1);
	i = -1;
	while (++i < philo->arg->nbrphilo)
	{
		if (pthread_join(philo[i].t_my_enum, NULL) != 0)
		{
			main_destroy(arg, philo, forks, JOIN_FAIL);
			return (1);
		}
	}
	return (0);
}

void	monitoring(t_philo *philos, t_my_enum action_enum)
{
	char		*current_action[6];
	suseconds_t	timesta;

	current_action[0] = DEAD_STR;
	current_action[1] = EAT_STR;
	current_action[2] = THINK_STR;
	current_action[3] = SLEEP_STR;
	current_action[4] = TAKE_FORK_STR;
	pthread_mutex_lock(&philos->arg->mutex);
	if (philos->arg->the_end)
	{
		pthread_mutex_unlock(&philos->arg->mutex);
		return ;
	}
	timesta = get_time() - philos->arg->start_time;
	printf("%ld %d %s", timesta, philos->nbr_philo1,
		current_action[action_enum]);
	pthread_mutex_unlock(&philos->arg->mutex);
}
