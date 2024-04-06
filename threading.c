#include "philo.h"


static void	mutex_init(t_info *dlist, int nbr_forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&dlist->m_dead, NULL);
	pthread_mutex_init(&dlist->ph_write, NULL);
	while (i < nbr_forks)
	{
		pthread_mutex_init(&dlist->forks[i], NULL);
		i++;
	}
}

static void	thread_join(t_info *dlist, t_philo *philo, pthread_t *thread, pthread_t super)
{
	int			i;

	i = 0;

	while (i < dlist->nbr_philo)
	{
		philo[i].dlist = dlist;
		philo[i].index_ph = i;
		philo[i].finished = 0;
		pthread_mutex_init(&philo[i].m_ph, NULL);
		pthread_create(&thread[i], NULL, philo_action, &philo[i]);
		i++;
	}
	pthread_create(&super, NULL, supervisor, philo);
	pthread_join(super, NULL);
	i = 0;
	while (i < dlist->nbr_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < dlist->nbr_philo)
	{
		pthread_mutex_destroy(&philo[i].m_ph);
		pthread_mutex_destroy(&dlist->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dlist->m_dead);


}

pthread_t	*threading(t_info *dlist)
{
	pthread_t	*thread;
	pthread_t	super;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * dlist->nbr_philo);
	if (!philo)
		return (0);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * dlist->nbr_philo);
	if (!thread)
		return (/*free(philo),*/ 0);
	mutex_init(dlist, dlist->nbr_philo);

	dlist->start_time = current_time();
	thread_join(dlist, philo, thread, super);
	return (thread);
}
