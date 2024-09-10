/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:08:19 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/29 14:06:50 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	destroy(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (arg)
		pthread_mutex_destroy(&arg->mutex);
	while (i < arg->nbrphilo)
	{
		pthread_mutex_destroy(&forks[i]);
		philo[i].left = NULL;
		philo[i].right = NULL;
		i++;
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
}

int	main_destroy(t_arg *arg, t_philo *philo, pthread_mutex_t *forks,
		char *error_msg)
{
	destroy(arg, philo, forks);
	write(2, "Error :", 8);
	write(2, error_msg, ft_strlen(error_msg));
	printf("\n");
	return (EXIT_FAILURE);
}

void	free_forks(pthread_mutex_t *forks, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

long	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (str[i] == '+' || str[i] == '-' || str[i] == '\0')
			return (2147483649);
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = (res * 10) + str[i] - 48;
		i++;
		if (res * sign > 2147483647 || res * sign < -2147483648)
			return (2147483649);
	}
	return (res * sign);
}
