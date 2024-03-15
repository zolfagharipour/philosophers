#include "philo.h"

static void	define_forks(t_philo *philo, int *dominant, int *passive)
{
	if (philo->index_ph % 2 == 0)
	{
		*dominant = philo->index_ph;
		*passive = (philo->index_ph + 1) % philo->dlist->nbr_philo;
	}
	else
	{
		*dominant = (philo->index_ph + 1) % philo->dlist->nbr_philo;
		*passive = philo->index_ph;
	}
}


static void	philo_do(t_philo *philo)
{
	int	dominant_fork;
	int	passive_fork;
	int	times_ate;

	times_ate = 0;
	define_forks(philo, &dominant_fork, &passive_fork);
	while (times_ate != philo->dlist->must_eat)
	{
		printf ("%ld %d is thinking.\n", current_time() - philo->dlist->start_time, philo->index_ph);
		pthread_mutex_lock(&philo->dlist->forks[dominant_fork]);
		printf ("%ld %d has taken a fork.\n", current_time() - philo->dlist->start_time, philo->index_ph);
		pthread_mutex_lock(&philo->dlist->forks[passive_fork]);
		printf ("%ld %d has taken a fork.\n", current_time() - philo->dlist->start_time, philo->index_ph);
		philo->last_ate = current_time();
		printf ("%ld %d is eating.\n", philo->last_ate - philo->dlist->start_time, philo->index_ph);
		ft_msleep(philo->dlist->time_to_eat);
		times_ate++;
		pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
		pthread_mutex_unlock(&philo->dlist->forks[passive_fork]);
		if (times_ate != philo->dlist->must_eat)
		{
			printf ("%ld %d is sleeping.\n", current_time()- philo->dlist->start_time, philo->index_ph);
			ft_msleep(philo->dlist->time_to_sleep);
		}
	}
}

void	*philo_action(void *arg)
{
	t_philo 		*philo;

	philo = (t_philo *)arg;
	philo->last_ate = current_time();
	philo_do(philo);
	return (NULL);
}
