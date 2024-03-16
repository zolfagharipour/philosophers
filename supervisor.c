#include "philo.h"

static int	check_philo(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < philo->dlist->nbr_philo)
	{
		if (current_time() - philo[i].last_ate > philo->dlist->time_to_die
			&& !philo[i].finished)
		{

			philo->dlist->dead = 1;
			return (i);
		}
		if (philo[i].finished)
			finished++;
		i++;
	}
	if (finished == philo->dlist->nbr_philo)
		return (FINISHED);
	return (ALIVE);
}


void	*supervisor(void *arg)
{
	t_philo *philo;
	int		check;
int a = 31;
	philo = (t_philo *)arg;
	check = ALIVE;
	while (check == ALIVE)
	{
		check = check_philo(philo);
	}
	if (check > ALIVE)
		printf ("\x1b[%dm%ld %d is dead.\x1b[0m\n", a, current_time() - philo[0].dlist->start_time,	check);
	return (NULL);
}