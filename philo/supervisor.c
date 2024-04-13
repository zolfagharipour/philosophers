/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:11:22 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 17:18:44 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].m_ph);
	if (current_time() - philo[i].last_ate > philo->dlist->time_to_die - 1
		&& !philo[i].finished)
	{
		pthread_mutex_lock(&philo[i].dlist->m_dead);
		philo->dlist->dead = 1;
		pthread_mutex_unlock(&philo[i].dlist->m_dead);
		pthread_mutex_unlock(&philo[i].m_ph);
		return (i);
	}
	else
	{
		pthread_mutex_unlock(&philo[i].m_ph);
		usleep(100);
	}
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
		pthread_mutex_lock(&philo[i].m_ph);
		if (philo[i].finished)
			finished++;
		pthread_mutex_unlock(&philo[i].m_ph);
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
		pthread_mutex_lock(&philo->dlist->ph_write);
		printf ("\x1b[31m%ld %d is dead.\x1b[0m\n",
			current_time() - philo[0].dlist->start_time, check + 1);
		pthread_mutex_unlock(&philo->dlist->ph_write);
	}
	return (NULL);
}
