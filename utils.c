#include "philo.h"

// suseconds_t		time(void)
// {
// 	return(2);
// }
void free_forks_until(pthread_mutex_t *forks, int until)
{
    int i;
    i = 0;
    while (i < until)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res * sign);
}
