/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oualid <oualid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:38 by ohassani          #+#    #+#             */
/*   Updated: 2024/07/24 00:30:19 by oualid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *non_function()
{
    printf("this the threads\n");
    return 0;
}
int  main(int argc, char **av)
{
    parsing(argc, av);
    t_arg arg;
    pthread_mutex_t *fork;
    t_philo *philos;
    if (argc == 5 || argc == 6)    
    	init_arg(&arg, av);
    fork = init_forks(&arg);
    philos = init_philo(&arg, fork);

    if(launch_thread(&arg, philos, fork) == 0)
        return(EXIT_FAILURE);
    (void)philos;
}
