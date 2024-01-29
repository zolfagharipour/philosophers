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



static t_philo	*philo_init(int ac, char **av, t_philo *philo)
{
	int	i;

	if (!error_check(ac, av))
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->nbr_philo = ft_atoi(av[1]);
	philo->forks = (int *)malloc(sizeof(int) * philo->nbr_philo);
	if (!philo->forks)
		return (NULL);
	i = 0;
	while (i < philo->nbr_philo)
	{
		philo->forks[i] = 0;
		i++;
	}
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->must_eat = ft_atoi(av[5]);
	else
		philo->must_eat = 0;
	return (philo);
}

int main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	*thread;


	philo = philo_init(ac, av, philo);
	if (!philo)
		return (0);
	thread = threading(philo);
	if (!thread)
		return (0);
	sleep (1);
	free(thread);
	struct_free(philo);
}