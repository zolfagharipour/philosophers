#include "philo.h"

void	*supervisor(void *arg)
{
	t_philo 	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutext_last_ate);
	while (current_time() - philo->last_ate < philo->dlist->time_to_die)
	{
		pthread_mutex_unlock(&philo->mutext_last_ate);
		usleep(100);
		pthread_mutex_lock(&philo->mutext_last_ate);
	}
	pthread_mutex_unlock(&philo->mutext_last_ate);
	printf ("\x1b[31m%ld %d is dead %ld.\x1b[0m\n", current_time(), philo->index_ph, philo->last_ate);
	pthread_mutex_lock(&philo->dlist->mutex_status);
	philo->dlist->status += 1;
	pthread_mutex_unlock(&philo->dlist->mutex_status);
}

static void	philo_do(t_philo *philo)
{
	int	left_fork;
	int	times_ate;

	times_ate = 0;
	pthread_mutex_lock(&philo->mutext_last_ate);
	philo->last_ate = current_time();
	pthread_mutex_unlock(&philo->mutext_last_ate);
	while (times_ate < philo->dlist->must_eat)
	{
		printf ("%ld %d is thinking.\n", current_time(), philo->index_ph);

		left_fork = (philo->index_ph - 1) % philo->dlist->nbr_philo;
		pthread_mutex_lock(&philo->dlist->forks[philo->index_ph]);
		pthread_mutex_lock(&philo->dlist->forks[left_fork]);
		pthread_mutex_lock(&philo->mutext_last_ate);
		philo->last_ate = current_time();
		pthread_mutex_unlock(&philo->mutext_last_ate);
		printf ("%ld %d is eating.\n", philo->last_ate, philo->index_ph);
		ft_msleep(philo->dlist->time_to_eat);
		times_ate++;
		pthread_mutex_unlock(&philo->dlist->forks[philo->index_ph]);
		pthread_mutex_unlock(&philo->dlist->forks[left_fork]);

		if (times_ate < philo->dlist->must_eat)
		{
			printf ("%ld %d is sleeping.\n", current_time(), philo->index_ph);
			ft_msleep(philo->dlist->time_to_sleep);
		}
	}
}

void	*philo_action(void *arg)
{
	pthread_t		thread;
	t_philo 		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_init(&philo->mutext_last_ate, NULL);
	// philo->last_ate = current_time();
	pthread_create(&thread, NULL, supervisor, philo);
	philo_do(philo);
	pthread_mutex_lock(&philo->dlist->mutex_status);
	philo->dlist->status += 10;
	pthread_mutex_unlock(&philo->dlist->mutex_status);
	pthread_detach(thread);
}
