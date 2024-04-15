/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:39:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/15 18:18:07 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	fork_create(t_philo *philo)
{
	int			i;
	int			j;

	i = 0;
	while (i < philo->nbr_philo)
	{
		philo->index_ph = i;
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			break;
		if (philo->pid[i] == 0)
			philo_action(philo);
		i++;
	}
	if (i != philo->nbr_philo)
	{
		j = 0;
		while (j < i)
		{
			kill(philo->pid[j], SIGKILL);
			j++;
		}
	}
}

static void	fork_wait(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->nbr_philo)
	{
		if (waitpid(philo->pid[i], NULL, 0) == -1)
			return ;
	}
}

static void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->s_dead);
	massacre_children(philo);
	return (NULL);
}

int	forking(t_philo *philo)
{
	pthread_t	super;
	
	philo->start_time = current_time();
	fork_create(philo);
	if (pthread_create(&super, NULL, supervisor, philo))
		return (massacre_children(philo));
	fork_wait(philo);
	return (1);
}
