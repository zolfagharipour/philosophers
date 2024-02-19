#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


# define TOO_FEW 6
# define TOO_MANY 7


typedef struct s_info
{
    pthread_mutex_t *forks;
    pthread_mutex_t mutex_status;
	int				status;
	int				nbr_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat;

}	t_info;

typedef struct s_philo
{
	struct s_info	*dlist;
	int				index_ph;
    pthread_mutex_t mutext_last_ate;
	long int		last_ate;
} t_philo;


int	ft_atoi(const char *nptr);
pthread_t	*threading(t_info *philo);
void	*philo_action(void *arg);
void	struct_free(t_philo *philo);
long int	current_time(void);
void	ft_msleep(long int usec);






#endif