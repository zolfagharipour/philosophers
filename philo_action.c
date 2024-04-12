/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:08:50 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 17:24:44 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	define_forks(t_philo *philo, int *dominant, int *passive)
{
	if (philo->index_ph % 2 == 0
		&& philo->index_ph != philo->dlist->nbr_philo - 1)
	{
		*dominant = philo->index_ph;
		*passive = (philo->index_ph + 1) % philo->dlist->nbr_philo;
	}
	else
	{
		*dominant = (philo->index_ph + 1) % philo->dlist->nbr_philo;
		*passive = philo->index_ph;
	}
}

void	philo_think(t_philo *philo)
{
	philo_write(philo, "is thinking");
	pthread_mutex_lock(&philo->m_ph);
	if (philo->dlist->nbr_philo % 2 == 1)
	{
		if (philo->dlist->time_to_die - (philo->last_ate - current_time())
			> philo->dlist->time_to_eat + 10)
		{
			pthread_mutex_unlock(&philo->m_ph);
			ft_msleep(philo->dlist->time_to_eat, philo);
		}
		else
			pthread_mutex_unlock(&philo->m_ph);
	}
	else
		pthread_mutex_unlock(&philo->m_ph);
}

static void	philo_eat(t_philo *philo, int dominant_fork, int passive_fork)
{
	pthread_mutex_lock(&philo->dlist->forks[dominant_fork]);
	philo_write(philo, "has taken a fork.D");
	if (dominant_fork == passive_fork)
	{
		pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->dlist->forks[passive_fork]);
	philo_write(philo, "has taken a fork.P");
	pthread_mutex_lock(&philo->m_ph);
	philo->last_ate = current_time();
	pthread_mutex_unlock(&philo->m_ph);
	philo_write(philo, "is eating");
	ft_msleep(philo->dlist->time_to_eat, philo);
	pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
	pthread_mutex_unlock(&philo->dlist->forks[passive_fork]);
}

static void	philo_do(t_philo *philo)
{
	int	dominant_fork;
	int	passive_fork;
	int	times_ate;

	times_ate = 0;
	define_forks(philo, &dominant_fork, &passive_fork);
	if ((philo->index_ph + 2) % 2 == 1)
		ft_msleep(philo->dlist->time_to_eat * 0.9, philo);
	while (times_ate != philo->dlist->must_eat && is_dead(philo))
	{
		philo_think(philo);
		philo_eat(philo, dominant_fork, passive_fork);
		times_ate++;
		if (times_ate != philo->dlist->must_eat)
		{
			philo_write(philo, "is sleeping");
			ft_msleep(philo->dlist->time_to_sleep, philo);
		}
	}
	pthread_mutex_lock(&philo->m_ph);
	philo->finished = 1;
	pthread_mutex_unlock(&philo->m_ph);
}

void	*philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->m_ph);
	philo->last_ate = current_time();
	pthread_mutex_unlock(&philo->m_ph);
	philo_do(philo);
	return (NULL);
}
