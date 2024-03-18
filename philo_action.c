#include "philo.h"

static void	define_forks(t_philo *philo, int *dominant, int *passive)
{
	if (philo->index_ph % 2 == 0 && philo->index_ph != philo->dlist->nbr_philo - 1)
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
	while (times_ate != philo->dlist->must_eat && !philo->dlist->dead)
	{
		pthread_mutex_lock(&philo->dlist->m_dead);
		if (!philo->dlist->dead)
			printf ("\x1b[%dm%ld %d is thinking.\x1b[0m\n", philo->index_ph +32, current_time() - philo->dlist->start_time, philo->index_ph);
		pthread_mutex_lock(&philo->dlist->forks[dominant_fork]);
		if (!philo->dlist->dead)
			printf ("\x1b[%dm%ld %d has taken a fork.D %d\n\x1b[0m", philo->index_ph+32, current_time() - philo->dlist->start_time, philo->index_ph, dominant_fork);
		pthread_mutex_lock(&philo->dlist->forks[passive_fork]);
		if (!philo->dlist->dead)
			printf ("\x1b[%dm%ld %d has taken a fork.P %d\n\x1b[0m", philo->index_ph+32, current_time() - philo->dlist->start_time, philo->index_ph, passive_fork);
		pthread_mutex_lock(&philo->m_ph);
		philo->last_ate = current_time();
		pthread_mutex_unlock(&philo->m_ph);
		if (!philo->dlist->dead)
			printf ("\x1b[%dm%ld %d is eating.\n\x1b[0m", philo->index_ph+32, philo->last_ate - philo->dlist->start_time, philo->index_ph);
		ft_msleep(philo->dlist->time_to_eat);
		times_ate++;
		pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
		pthread_mutex_unlock(&philo->dlist->forks[passive_fork]);
		if (times_ate != philo->dlist->must_eat && !philo->dlist->dead)
		{
			printf ("\x1b[%dm%ld %d is sleeping.\n\x1b[0m", philo->index_ph+32, current_time()- philo->dlist->start_time, philo->index_ph);
			ft_msleep(philo->dlist->time_to_sleep);
		}
		pthread_mutex_unlock(&philo->dlist->m_dead);
		// usleep(100);
	}
	pthread_mutex_lock(&philo->m_ph);
	philo->finished = 1;
	pthread_mutex_unlock(&philo->m_ph);
}

void	*philo_action(void *arg)
{
	t_philo 		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->m_ph);
	philo->last_ate = current_time();
	pthread_mutex_unlock(&philo->m_ph);
	philo_do(philo);
	return (NULL);
}
