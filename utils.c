#include "philo.h"

long int	current_time(void)
{
	struct timeval	tv_current;

    gettimeofday(&tv_current, NULL);
	return (tv_current.tv_usec / 1000 + tv_current.tv_sec * 1000);
}

void	ft_msleep(long int msec)
{
	long int	start;

	start = current_time();
	while (current_time() - start <= msec -1)
		usleep(100);
	// check if someone is dead
}

void	struct_free(t_philo *philo)
{
	// free(philo->forks);
	// free(philo);
}