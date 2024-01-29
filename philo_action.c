#include "philo.h"

static void	eat(t_philo *philo, struct timeval *tv_last)
{
	
}

static void	think(t_philo *philo)
{

}

static void	sleep_p(t_philo *philo)
{

}

void	*philo_action(void *arg)
{
	long int		last_ate;
	t_philo 		*philo;
    struct timeval	tv_last;
    struct timeval	tv_current;


	philo = (t_philo *)arg;
	gettimeofday(&tv_last, NULL);
	gettimeofday(&tv_current, NULL);
	while (tv_current.tv_usec - tv_last.tv_usec < philo->time_to_die)
	{
		eat(philo, &tv_last);
		think(philo);
		sleep_p(philo);
		gettimeofday(&tv_current, NULL);
	}

}