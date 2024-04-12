/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:40:26 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 18:54:20 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	current_time(void)
{
	struct timeval	tv_current;

	if (gettimeofday(&tv_current, NULL) == -1)
		return (0);
	return (tv_current.tv_usec / 1000 + tv_current.tv_sec * 1000);
}

int	is_dead(t_philo *philo)
{
	sem_wait(philo->dlist->s_dead);
	if (!philo->dlist->dead)
	{
		sem_post(philo->dlist->s_dead);
		return (1);
	}
	sem_post(philo->dlist->s_dead);
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
	while (current && current - start <= msec - 1)
	{
		usleep(100);
		if (!is_dead(philo))
			return ;
		current = current_time();
	}
}
