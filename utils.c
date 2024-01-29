#include "philo.h"

void	struct_free(t_philo *philo)
{
	free(philo->forks);
	free(philo);
}