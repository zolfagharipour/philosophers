#include "philo.h"

static int	check_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->dlist->nbr_philo)
	{
		if (current_time() - philo[i].last_ate > philo->dlist->time_to_die)
		{
			printf ("	%d - %ld - %ld\n", i, current_time() - philo[i].last_ate, philo->dlist->time_to_die);
			return (i);
		}
		i++;
	}
	return (-1);
}


void	*supervisor(void *arg)
{
	t_philo *philo;
	int		check;

	philo = (t_philo *)arg;
	check = -1;
	usleep(5000);
			write (2, "BINGO\n", 7);
	while (check == -1)
	{
		check = check_philo(philo);
	}
	printf ("\x1b[31m%ld %d is dead.\x1b[0m\n", current_time() - philo[0].dlist->start_time,	check);
	return (NULL);
}