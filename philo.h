#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TOO_FEW 6
# define TOO_MANY 7


typedef struct s_philo
{
	int			*forks;
	int			*status;
	int			nbr_philo;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int			must_eat;
    pthread_mutex_t mutex;

}	t_philo;

int	ft_atoi(const char *nptr);
pthread_t	*threading(t_philo *philo);
void	*philo_action(void *arg);
void	struct_free(t_philo *philo);




#endif