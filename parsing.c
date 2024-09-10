/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:19:17 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/31 17:06:41 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_and_join_guard_thread(t_arg *arg, t_philo *philo,
		pthread_mutex_t *forks)
{
	pthread_t	guard_thread;

	if (pthread_create(&guard_thread, NULL, guard, (void *)philo) != 0)
	{
		main_destroy(arg, philo, forks, FAIL_THREAD);
		return (1);
	}
	if (pthread_join(guard_thread, NULL) != 0)
	{
		main_destroy(arg, philo, forks, JOIN_FAIL);
		return (1);
	}
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_is_digit1(char **av)
{
	int	i;
	int	j;

	i = 1;
	skip_spaces(av);
	while (av[i])
	{
		j = 0;
		if (av[i][0] == '+')
			j = 1;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (fd < 0 || s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	parsing(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || ft_is_digit1(av) == 1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}
