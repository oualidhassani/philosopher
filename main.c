/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:38 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/31 16:43:14 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **av)
{
	t_arg			arg;
	pthread_mutex_t	*fork;
	t_philo			*philos;

	(void)argc;
	if (parsing(argc, av))
		return (EXIT_FAILURE);
	if (!init_arg(&arg, av))
		return (EXIT_FAILURE);
	fork = init_forks(&arg);
	philos = init_philo(&arg, fork);
	if (launch_thread(&arg, philos, fork) != 0)
		return (EXIT_FAILURE);
	destroy(&arg, philos, fork);
}
