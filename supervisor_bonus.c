/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:39:04 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 18:50:23 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	if_dead(t_philo *philo, int i)
{
	sem_wait(philo[i].s_ph);
	if (current_time() - philo[i].last_ate > philo->dlist->time_to_die - 1
		&& !philo[i].finished)
	{
		sem_post(philo[i].s_ph);
		sem_wait(philo[i].dlist->s_dead);
		philo->dlist->dead = 1;
		sem_post(philo[i].dlist->s_dead);
		return (i);
	}
	else
		sem_post(philo[i].s_ph);
	return (ALIVE);
}

static int	check_philo(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	usleep(50 * philo->dlist->nbr_philo);
	while (i < philo->dlist->nbr_philo)
	{
		if (if_dead(philo, i) != ALIVE)
			return (i);
		sem_wait(philo[i].s_ph);
		if (philo[i].finished)
			finished++;
		sem_post(philo[i].s_ph);
		i++;
	}
	if (finished == philo->dlist->nbr_philo)
		return (FINISHED);
	return (ALIVE);
}

void	*supervisor(void *arg)
{
	t_philo	*philo;
	int		check;

	philo = (t_philo *)arg;
	check = ALIVE;
	while (check == ALIVE)
	{
		check = check_philo(philo);
	}
	if (check > ALIVE)
	{
		sem_wait(philo->dlist->ph_write);
		printf ("\x1b[31m%ld %d is dead.\x1b[0m\n",
			current_time() - philo[0].dlist->start_time, check);
		sem_post(philo->dlist->ph_write);
	}
	return (NULL);
}
