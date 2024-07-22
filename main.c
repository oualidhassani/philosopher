/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:38 by ohassani          #+#    #+#             */
/*   Updated: 2024/07/15 19:38:10 by ohassani         ###   ########.fr       */
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
    pthread_t t1;
    
    pthread_create(&t1, NULL, &non_function , NULL);
    pthread_join(t1, NULL);
}