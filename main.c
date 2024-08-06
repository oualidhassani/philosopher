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
int  main(int ac, char **av)
{
    parsing(ac, av);
    t_arg arg;
    pthread_mutex_t *fork;
    t_philo *philos;
    
    init_arg(&arg, av);
    fork = init_forks(&arg);
    philos = init_philo(&arg, fork);

    (void)philos;
}