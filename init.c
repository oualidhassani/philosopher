/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:36 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/26 15:28:17 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_arg *arg, pthread_mutex_t *the_forks)
{
	t_philo	*philo;
	int		i;

	philo = malloc(arg->nbrphilo * sizeof(t_philo));
	i = 0;
	while (i < arg->nbrphilo)
	{
		philo[i].nbr_philo1 = i + 1;
		philo[i].left = &the_forks[i];
		philo[i].right = &the_forks[(i + 1) % arg->nbrphilo];
		philo[i].meals_eat = 0;
		philo[i].last_meal = get_time();
		philo[i].arg = arg;
		i++;
	}
	return (philo);
}

bool	init_arg(t_arg *arg, char **av)
{
	arg->nbrphilo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	arg->times_each_philosopher_must_eat = -1;
	if (av[5])
		arg->times_each_philosopher_must_eat = ft_atoi(av[5]);
	if (arg->nbrphilo == 0 || arg->time_to_die == 0 || arg->time_sleep == 0
		|| arg->time_to_eat == 0)
		ft_putstr_fd("Error\n", 2);
	if (pthread_mutex_init(&arg->mutex, NULL) != 0)
	{
		main_destroy(0, NULL, NULL, INIT_MUTEX);
		return (false);
	}
	arg->the_end = false;
	return (true);
}

pthread_mutex_t	*init_forks(t_arg *arg)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(arg->nbrphilo * sizeof(pthread_mutex_t));
	i = 0;
	if (!fork)
		main_destroy(arg, NULL, NULL, MALLOC_FAIL);
	while (arg->nbrphilo > i)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			free_forks(fork, i);
		i++;
	}
	return (fork);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

suseconds_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}
