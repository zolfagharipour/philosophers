/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:40:26 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/17 13:10:21 by mzolfagh         ###   ########.fr       */
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
		check_dead(philo);
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

void	check_dead(t_philo *philo)
{
	sem_wait(philo->s_ph);
	if (current_time() - philo->last_ate > philo->time_to_die - 1)
	{
		sem_post(philo->s_ph);
		sem_wait(philo->ph_write);
		printf ("\x1b[31m%ld %d is dead.\x1b[0m\n",
			current_time() - philo->start_time, philo->index_ph + 1);
		sem_close(philo->s_ph);
		sem_unlink("s_ph");
		sem_close(philo->forks);
		sem_close(philo->ph_write);
		sem_unlink("forks");
		sem_unlink("ph_write");
		sem_close(philo->s_dead);
		sem_unlink("s_dead");
		exit(EXIT_FAILURE);
	}
	else
	{
		sem_post(philo->s_ph);
		usleep(100);
	}
}
