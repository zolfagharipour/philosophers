#include "philo.h"

static int	check_philo(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < philo->dlist->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].m_ph);
		if (current_time() - philo[i].last_ate > philo->dlist->time_to_die
			&& !philo[i].finished)
		{
	printf("{%ld}\n", current_time() - philo[i].last_ate);
			pthread_mutex_lock(&philo[i].dlist->m_dead);
			philo->dlist->dead = 1;
			pthread_mutex_unlock(&philo[i].dlist->m_dead);
			pthread_mutex_unlock(&philo[i].m_ph);
			return (i);
		}
		if (philo[i].finished)
			finished++;
		pthread_mutex_unlock(&philo[i].m_ph);
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