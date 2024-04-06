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

static void	philo_write(t_philo *philo, char *print)
{
	pthread_mutex_lock(&philo->dlist->m_dead);
	if (!philo->dlist->dead)
	{
		pthread_mutex_unlock(&philo->dlist->m_dead);
		pthread_mutex_lock(&philo->dlist->ph_write);
		printf ("%ld\t%d\t%s\n", current_time() - philo->dlist->start_time, philo->index_ph, print);
		pthread_mutex_unlock(&philo->dlist->ph_write);
	}
	else
		pthread_mutex_unlock(&philo->dlist->m_dead);
}

static int is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dlist->m_dead);
	if (!philo->dlist->dead)
	{
		pthread_mutex_unlock(&philo->dlist->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->dlist->m_dead);
	return (0);
}

static void	philo_do(t_philo *philo)
{
	int	dominant_fork;
	int	passive_fork;
	int	times_ate;

	times_ate = 0;
	define_forks(philo, &dominant_fork, &passive_fork);
	if ((philo->index_ph + 2) % 2 == 1)
	{
			ft_msleep(philo->dlist->time_to_eat);
	}
	while (times_ate != philo->dlist->must_eat && is_dead(philo))
	{
		pthread_mutex_lock(&philo->dlist->forks[dominant_fork]);
		philo_write(philo, "has taken a fork.D");
		pthread_mutex_lock(&philo->dlist->forks[passive_fork]);
		philo_write(philo, "has taken a fork.P");
		pthread_mutex_lock(&philo->m_ph);
		philo->last_ate = current_time();
		pthread_mutex_unlock(&philo->m_ph);
		philo_write(philo, "is eating");
		ft_msleep(philo->dlist->time_to_eat);
		times_ate++;
		pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
		pthread_mutex_unlock(&philo->dlist->forks[passive_fork]);
		if (times_ate != philo->dlist->must_eat)
		{
			philo_write(philo, "is sleeping");
			ft_msleep(philo->dlist->time_to_sleep);
		}
		philo_write(philo, "is thinking");
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
