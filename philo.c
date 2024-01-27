#include "philo.h"

static int	philo_init(int ac, char **av, t_philo *philo)
{
	if (ac < 5)
	{
		write (2, "too few arguments", 18);
		return (0);
	}
	else if (ac > 6)
	{
		write (2, "too many arguments", 19);
		return (0);
	}
	philo->nbr_philo = atoi(av[1]);
	philo->forks = (int *)malloc(sizeof(int) * philo->nbr_philo);
	if (philo->forks)
		return (0);
	philo->forks[0] = 12;
	philo->must_eat = 0;
 

}

int main(int ac, char **av)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	philo_init(ac, av, philo);
	printf("%d\n", philo->forks[0]);
}