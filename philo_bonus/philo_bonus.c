/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:35:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/17 13:04:02 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	error_print(int i)
{
	if (i == 1)
		write(2, "Number of philosophers is not correct.\n", 40);
	else if (i == 2)
		write(2, "Time to die is not correct.\n", 29);
	else if (i == 3)
		write(2, "Time to eat is not correct.\n", 29);
	else if (i == 4)
		write(2, "Time to sleep is not correct.\n", 31);
	else if (i == 5)
		write(2, "number of times each philo must eat is not correct.\n", 53);
	else if (i == TOO_FEW)
		write(2, "Too few arguments.\n", 20);
	else if (i == TOO_MANY)
		write(2, "Too many arguments.\n", 21);
	else if (i == TOO_MANY_PHILO)
		write(2, "Too many philosophers.\n", 24);
	return (0);
}

static int	error_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
		return (error_print(TOO_FEW));
	else if (ac > 6)
		return (error_print(TOO_MANY));
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (error_print(i));
		i++;
	}
	return (1);
}

static int	semaphors_open(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("s_dead");
	sem_unlink("ph_write");
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->nbr_philo);
	if (philo->forks == SEM_FAILED)
		return (0);
	philo->s_dead = sem_open("s_dead", O_CREAT, 644, philo->nbr_philo);
	if (philo->s_dead == SEM_FAILED)
	{
		sem_close(philo->forks);
		return (sem_unlink("forks"), 0);
	}
	philo->ph_write = sem_open("ph_write", O_CREAT, 644, 1);
	if (philo->ph_write == SEM_FAILED)
	{
		sem_close(philo->forks);
		sem_close(philo->s_dead);
		return (sem_unlink("forks"), sem_unlink("s_dead"), 0);
	}
	return (1);
}

static int	philo_init(int ac, char **av, t_philo *philo)
{
	if (!error_check(ac, av))
		return (0);
	philo->nbr_philo = ft_atoi(av[1]);
	if (philo->nbr_philo > 499)
		return (error_print(TOO_MANY_PHILO));
	if (!semaphors_open(philo))
		return (0);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->must_eat = ft_atoi(av[5]);
	else
		philo->must_eat = -1;
	philo->finished = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		philo;

	if (!philo_init(ac, av, &philo))
		return (0);
	forking(&philo);
	sem_close(philo.forks);
	sem_close(philo.s_dead);
	sem_close(philo.ph_write);
	sem_unlink("forks");
	sem_unlink("s_dead");
	sem_unlink("ph_write");
}
