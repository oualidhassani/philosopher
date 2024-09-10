/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:08:33 by ohassani          #+#    #+#             */
/*   Updated: 2024/08/31 16:44:54 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INIT_MUTEX "fail the mutex initialization"
# define FAIL_THREAD "fail the creation of the thread"
# define JOIN_FAIL "fail the join"
# define MALLOC_FAIL "malloc fail"
# define PARSING_ERROR "error in arguments"

// struct of agrs
typedef struct s_arg
{
	long			nbrphilo;
	long			time_to_die;
	long			time_to_eat;
	long			time_sleep;
	long			times_each_philosopher_must_eat;
	pthread_mutex_t	mutex;
	suseconds_t		start_time;
	bool			the_end;
}					t_arg;

/// sturct of philos
typedef struct s_philo
{
	int				nbr_philo1;
	suseconds_t		time;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				meals_eat;
	suseconds_t		last_meal;
	pthread_t		t_my_enum;
	t_arg			*arg;
}					t_philo;

// struct of enum
typedef enum e_my_enum
{
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
}					t_my_enum;

// parsing
int					parsing(int ac, char **av);

// init
pthread_mutex_t		*init_forks(t_arg *arg);
bool				init_arg(t_arg *arg, char **av);
t_philo				*init_philo(t_arg *arg, pthread_mutex_t *the_forks);

// utils
long				ft_atoi(char *str);
void				ft_putstr_fd(char *s, int fd);
void				free_forks(pthread_mutex_t *forks, int until);

// destroy
int					main_destroy(t_arg *arg, t_philo *philo,
						pthread_mutex_t *forks, char *error_msg);

// create the thread
int					launch_thread(t_arg *arg, t_philo *philo,
						pthread_mutex_t *forks);
void				monitoring(t_philo *philos, t_my_enum action_enum);
int					create_and_join_guard_thread(t_arg *arg, t_philo *philo,
						pthread_mutex_t *forks);

// get the time
suseconds_t			get_time(void);
int					ft_usleep(size_t milliseconds);

// the forks
void				pick_the_fork(t_philo *philo);
void				drop_the_fork(t_philo *philo);
void				eat_that_meal(t_philo *philo);
void				philo_sleeping(t_philo *philo);

// the dead of the philos
bool				starv(t_philo *philo);
void				*guard(void *philos_void);
void				destroy(t_arg *arg, t_philo *philo, pthread_mutex_t *forks);
bool				is_philo_dead(t_philo *philos, int *satisfed_philo);
void				skip_spaces(char **av);
#endif
