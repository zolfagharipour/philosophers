#include "philo.h"


pthread_t	*threading(t_philo *philo)
{
	pthread_t	*thread;
	int	i;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->nbr_philo);
	if (!thread)
		return (0);
	i = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	while (i < philo->nbr_philo)
	{
		pthread_create(&thread[i], NULL, philo_action, philo);
		pthread_join(thread[i], NULL);
		i++;
	}
	return (thread);
}
