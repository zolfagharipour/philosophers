/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:39:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/17 13:11:01 by mzolfagh         ###   ########.fr       */
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
			break ;
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
	int		wstatus;

	i = 0;
	wstatus = 0;
	while (i < philo->nbr_philo)
	{
		if (waitpid(-1, &wstatus, 0) == -1)
			return ;
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_FAILURE)
			massacre_children(philo);
		i++;
	}
}

int	forking(t_philo *philo)
{
	philo->start_time = current_time();
	fork_create(philo);
	fork_wait(philo);
	return (1);
}
