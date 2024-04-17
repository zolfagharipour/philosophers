/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:24:00 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/17 15:16:34 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_write(t_philo *philo, char *print)
{
	sem_wait(philo->ph_write);
	printf ("%ld\t%d\t%s\n", current_time() - philo->start_time,
		philo->index_ph + 1, print);
	sem_post(philo->ph_write);
}

void	philo_think(t_philo *philo)
{
	philo_write(philo, "is thinking");
	sem_wait(philo->s_ph);
	if (philo->nbr_philo % 2 == 1)
	{
		if (philo->time_to_die - (philo->last_ate - current_time())
			> philo->time_to_eat)
		{
			sem_post(philo->s_ph);
			ft_msleep(philo->time_to_eat, philo);
		}
		else
			sem_post(philo->s_ph);
	}
	else
		sem_post(philo->s_ph);
}

static void	philo_eat(t_philo *philo)
{
	check_dead(philo);
	sem_wait(philo->forks);
	philo_write(philo, "has taken a fork.");
	if (philo->nbr_philo == 1)
		ft_msleep(philo->time_to_die, philo);
	check_dead(philo);
	sem_wait(philo->forks);
	philo_write(philo, "has taken a fork.");
	sem_wait(philo->s_ph);
	philo->last_ate = current_time();
	sem_post(philo->s_ph);
	philo_write(philo, "is eating");
	ft_msleep(philo->time_to_eat, philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

static void	philo_do(t_philo *philo)
{
	int	times_ate;

	times_ate = 0;
	if (philo->index_ph % 2 == 1)
		ft_msleep(philo->time_to_eat, philo);
	while (times_ate != philo->must_eat)
	{
		philo_think(philo);
		philo_eat(philo);
		times_ate++;
		if (times_ate != philo->must_eat)
		{
			philo_write(philo, "is sleeping");
			ft_msleep(philo->time_to_sleep, philo);
		}
	}
}

void	philo_action(t_philo *philo)
{
	sem_unlink("s_ph");
	philo->s_ph = sem_open("s_ph", O_CREAT, 0644, 1);
	if (philo->s_ph == SEM_FAILED)
		exit(EXIT_FAILURE);
	sem_wait(philo->s_ph);
	philo->last_ate = current_time();
	sem_post(philo->s_ph);
	philo_do(philo);
	sem_wait(philo->s_ph);
	philo->finished = 1;
	sem_post(philo->s_ph);
	usleep(1000);
	sem_close(philo->forks);
	sem_close(philo->s_dead);
	sem_close(philo->ph_write);
	sem_unlink("forks");
	sem_unlink("s_dead");
	sem_unlink("ph_write");
	sem_close(philo->s_ph);
	sem_unlink("s_ph");
	exit(EXIT_SUCCESS);
}
