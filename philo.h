#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			*forks;
	int			nbr_philo;
	long int	last_meal_time;
	long int	time_to_die;
	long int	time_to_eat;
	int			must_eat;

}	t_philo;

#endif