#include "philo.h"

static int	error_print(int	i)
{
	if (i == 1)
		write(2, "Number of philosophers is not correct.", 39);
	else if (i == 2)
		write(2, "Time to die is not correct.", 28);
	else if (i == 3)
		write(2, "Time to eat is not correct.", 28);
	else if (i == 4)
		write(2, "Time to sleep is not correct.", 30);
	else if (i == 5)
		write(2, "number of times each philosopher must eat is not correct.", 58);
	else if (i == TOO_FEW)
		write(2, "Too few arguments.", 19);
	else if (i == TOO_MANY)
		write(2, "Too many arguments.", 20);
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
	dlist->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * dlist->nbr_philo);
	if (!dlist->forks)
		return (free (dlist), NULL);
	dlist->time_to_die = ft_atoi(av[2]);
	dlist->time_to_eat = ft_atoi(av[3]);
	dlist->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dlist->must_eat = ft_atoi(av[5]);
	else
		dlist->must_eat = -1;
	return (dlist);
}

int main(int ac, char **av)
{
	t_info		*dlist;
	pthread_t	*thread;

	dlist = philo_init(ac, av, dlist);
	if (!dlist)
		return (0);
	thread = threading(dlist);
	if (!thread)
		return (/*struct_free(dlist),*/ 0);

	// pthread_mutex_lock(&dlist->mutex_status);
	// while (dlist->status % 10 == 0 && dlist->status != dlist->nbr_philo * 10)
	// {
	// 	pthread_mutex_unlock(&dlist->mutex_status);
	// 	usleep(100);
	// 	pthread_mutex_lock(&dlist->mutex_status);
	// }
	// pthread_mutex_unlock(&dlist->mutex_status);
	// HERE COMES THE ENDING SCENARIO
	free(thread);
	// struct_free(dlist);
}
