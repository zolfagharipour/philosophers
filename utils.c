/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:03:03 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 19:41:22 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_time(void)
{
	struct timeval	tv_current;

	if (gettimeofday(&tv_current, NULL) == -1)
		return (0);
	return (tv_current.tv_usec / 1000 + tv_current.tv_sec * 1000);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dlist->m_dead);
	if (!philo->dlist->dead)
	{
		pthread_mutex_unlock(&philo->dlist->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->dlist->m_dead);
	return (0);
}

void	ft_msleep(long int msec, t_philo *philo)
{
	long int	start;
	long int	current;

	start = current_time();
	if (!start)
		return ;
	current = current_time();
	while (current && current - start <= msec)
	{
		usleep(100);
		if (!is_dead(philo))
			return ;
		current = current_time();
	}
}

void	philo_write(t_philo *philo, char *print)
{
	pthread_mutex_lock(&philo->dlist->m_dead);
	if (!philo->dlist->dead)
	{
		pthread_mutex_unlock(&philo->dlist->m_dead);
		pthread_mutex_lock(&philo->dlist->ph_write);
		printf ("%ld\t%d\t%s\n", current_time() - philo->dlist->start_time,
			philo->index_ph + 1, print);
		pthread_mutex_unlock(&philo->dlist->ph_write);
	}
	else
		pthread_mutex_unlock(&philo->dlist->m_dead);
}
