/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:40:26 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/15 17:53:30 by mzolfagh         ###   ########.fr       */
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

void	ft_msleep(long int msec, t_philo *philo)
{
	long int	start;
	long int	current;

	(void) philo;
	start = current_time();
	if (!start)
		return ;
	current = current_time();
	while (current && current - start <= msec - 1)
	{
		usleep(100);
		current = current_time();
	}
}

int	massacre_children(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_philo)
	{
		kill(philo->pid[i], SIGKILL);
		i++;
	}
	return (0);
}
