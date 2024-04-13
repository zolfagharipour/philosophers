/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:24:00 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/13 17:59:34 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_write(t_philo *philo, char *print)
{
	sem_wait(philo->dlist->s_dead);
	if (!philo->dlist->dead)
	{
		sem_wait(philo->dlist->ph_write);
		sem_post(philo->dlist->s_dead);
		printf ("%ld\t%d\t%s\n", current_time() - philo->dlist->start_time,
			philo->index_ph + 1, print);
		sem_post(philo->dlist->ph_write);
	}
	else
		sem_post(philo->dlist->s_dead);
}

void	philo_think(t_philo *philo)
{
	philo_write(philo, "is thinking");
	sem_wait(philo->s_ph);
	if (philo->dlist->nbr_philo % 2 == 1)
	{
		if (philo->dlist->time_to_die - (philo->last_ate - current_time())
			> philo->dlist->time_to_eat)
		{
			sem_post(philo->s_ph);
			ft_msleep(philo->dlist->time_to_eat, philo);
		}
		else
			sem_post(philo->s_ph);
	}
	else
		sem_post(philo->s_ph);
}

static void	philo_eat(t_philo *philo)
{
	if (is_dead(philo))
	{
		sem_wait(philo->dlist->forks);
		if (!is_dead(philo))
		{
			sem_post(philo->dlist->forks);
			return ;
		}
		philo_write(philo, "has taken a fork.F");
		sem_wait(philo->dlist->forks);
		if (!is_dead(philo))
		{
			sem_post(philo->dlist->forks);
			return ;
		}
		philo_write(philo, "has taken a fork.S");
		sem_wait(philo->s_ph);
		philo->last_ate = current_time();
		sem_post(philo->s_ph);
		philo_write(philo, "is eating");
		ft_msleep(philo->dlist->time_to_eat, philo);
		sem_post(philo->dlist->forks);
		sem_post(philo->dlist->forks);
	}
}

static void	philo_do(t_philo *philo)
{
	int	times_ate;

	times_ate = 0;
	if (philo->index_ph % 2 == 1)
		ft_msleep(philo->dlist->time_to_eat, philo);
	while (times_ate != philo->dlist->must_eat && is_dead(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		times_ate++;
		if (times_ate != philo->dlist->must_eat)
		{
			philo_write(philo, "is sleeping");
			ft_msleep(philo->dlist->time_to_sleep, philo);
		}
	}
	sem_wait(philo->s_ph);
	philo->finished = 1;
	sem_post(philo->s_ph);
}

void	*philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->s_ph);
	philo->last_ate = current_time();
	sem_post(philo->s_ph);
	philo_do(philo);
	return (NULL);
}
