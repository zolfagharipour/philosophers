#include "philo.h"

long int	current_time(void)
{
	struct timeval	tv_current;

    gettimeofday(&tv_current, NULL);
	return (tv_current.tv_usec / 1000 + tv_current.tv_sec * 1000);
}
int is_dead(t_philo *philo)
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

void	ft_msleep(long int msec, t_philo *philo)
{
	long int	start;

	start = current_time();
	while (current_time() - start <= msec -1)
	{
		usleep(100);
		if (!is_dead(philo))
			return ;
	}
}
