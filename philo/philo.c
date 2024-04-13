/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:03:50 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/13 18:45:43 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static t_info	*philo_init(int ac, char **av, t_info *dlist)
{
	if (!error_check(ac, av))
		return (NULL);
	dlist = (t_info *)malloc(sizeof(t_info));
	if (!dlist)
		return (NULL);
	dlist->nbr_philo = ft_atoi(av[1]);
	dlist->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* dlist->nbr_philo);
	if (!dlist->forks)
		return (free (dlist), NULL);
	dlist->time_to_die = ft_atoi(av[2]);
	dlist->time_to_eat = ft_atoi(av[3]);
	dlist->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dlist->must_eat = ft_atoi(av[5]);
	else
		dlist->must_eat = -1;
	dlist->dead = 0;
	return (dlist);
}

int	main(int ac, char **av)
{
	t_info		*dlist;
	pthread_t	*thread;

	dlist = NULL;
	dlist = philo_init(ac, av, dlist);
	if (!dlist)
		return (0);
	thread = threading(dlist);
	free(thread);
	free(dlist->forks);
	free(dlist);
}
