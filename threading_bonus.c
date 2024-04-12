/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:39:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 18:40:18 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	thread_create(t_info *dlist, t_philo *philo,
	pthread_t *thread, pthread_t *super)
{
	int			i;
	sem_t		*s;

	i = 0;
	sem_unlink("/s_ph");
	s = sem_open("/s_ph", O_CREAT | O_EXCL, 0644, 1);
	if (s == SEM_FAILED)
		return (0);
	while (i < dlist->nbr_philo)
	{
		philo[i].dlist = dlist;
		philo[i].index_ph = i;
		philo[i].finished = 0;
		philo[i].s_ph = s;
		if (pthread_create(&thread[i], NULL, philo_action, &philo[i]))
			return (sem_close(s), sem_unlink("/s_ph"), i);
		i++;
	}
	if (pthread_create(super, NULL, supervisor, philo))
	{
		sem_close(s);
		sem_unlink("/s_ph");
		return (dlist->nbr_philo + 1);
	}
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
	dlist->start_time = current_time();
	i = thread_create(dlist, philo, thread, &super);
	thread_join(dlist, thread, &super, i);
	sem_close(philo->s_ph);
	sem_unlink("/s_ph");
	free(philo);
	return (thread);
}
