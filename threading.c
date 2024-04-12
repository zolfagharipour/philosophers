/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:12:45 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 17:14:01 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	thread_create(t_info *dlist, t_philo *philo,
	pthread_t *thread, pthread_t *super)
{
	int			i;

	i = 0;
	while (i < dlist->nbr_philo)
	{
		philo[i].dlist = dlist;
		philo[i].index_ph = i;
		philo[i].finished = 0;
		pthread_mutex_init(&philo[i].m_ph, NULL);
		if (pthread_create(&thread[i], NULL, philo_action, &philo[i]))
			return (i);
		i++;
	}
	if (pthread_create(super, NULL, supervisor, philo))
		return (dlist->nbr_philo + 1);
	return (-1);
}

static void	thread_join(t_info *dlist, pthread_t *thread,
	pthread_t *super, int i)
{
	int	j;

	if (i < 0)
	{
		i = dlist->nbr_philo;
		pthread_join(*super, NULL);
	}
	else if (i == dlist->nbr_philo + 1)
		i--;
	j = 0;
	while (j < i)
	{
		pthread_join(thread[j], NULL);
		j++;
	}
}

static void	philo_destroy(t_info *dlist, t_philo *philo, int i)
{
	int	j;

	j = 0;
	if (i < 0 || i == dlist->nbr_philo + 1)
		i = dlist->nbr_philo;
	while (j < i)
	{
		pthread_mutex_destroy(&philo[j].m_ph);
		pthread_mutex_destroy(&dlist->forks[j]);
		j++;
	}
	pthread_mutex_destroy(&dlist->m_dead);
	pthread_mutex_destroy(&dlist->ph_write);
}

pthread_t	*threading(t_info *dlist)
{
	t_philo		*philo;
	pthread_t	*thread;
	pthread_t	super;
	int			i;

	philo = (t_philo *)malloc(sizeof(t_philo) * dlist->nbr_philo);
	if (!philo)
		return (0);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * dlist->nbr_philo);
	if (!thread)
		return (free(philo), NULL);
	mutex_init(dlist, dlist->nbr_philo);
	dlist->start_time = current_time();
	i = thread_create(dlist, philo, thread, &super);
	thread_join(dlist, thread, &super, i);
	philo_destroy(dlist, philo, i);
	free(philo);
	return (thread);
}
