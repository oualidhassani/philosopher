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

int  main(int argc, char **av)
{
    if(parsing(argc, av))
        return(EXIT_FAILURE);
    t_arg arg;
    pthread_mutex_t *fork;
    t_philo *philos;
    if(!init_arg(&arg, av))
        return(EXIT_FAILURE);
    fork = init_forks(&arg);
    philos = init_philo(&arg, fork);

    if(launch_thread(&arg, philos, fork) == 0)
        return(EXIT_FAILURE);
    main_destroy(&arg, philos, fork ,ALL_DONE);
}
