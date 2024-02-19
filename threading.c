#include "philo.h"


static void	mutex_init(t_info *dlist, int nbr_forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&dlist->mutex_status, NULL);
	while (i < nbr_forks)
	{
		pthread_mutex_init(&dlist->forks[i], NULL);
		i++;
	}
}

pthread_t	*threading(t_info *dlist)
{
	pthread_t	*thread;
	t_philo		*philo;
	int	i;

	philo = (t_philo *)malloc(sizeof(t_philo) * dlist->nbr_philo);
	if (!philo)
		return (0);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * dlist->nbr_philo);
	if (!thread)
		return (free(philo), 0);
	i = 0;
	mutex_init(dlist, dlist->nbr_philo);
	while (i < dlist->nbr_philo)
	{
		philo[i].dlist = dlist;
		philo[i].index_ph = i;
		pthread_create(&thread[i], NULL, philo_action, &philo[i]);
		pthread_join(thread[i], NULL);
		i++;
	}
	return (thread);
}
