#include "philo_bonus.h"


static void	philo_write(t_philo *philo, char *print)
{
	// pthread_mutex_lock(&philo->dlist->m_dead);
	sem_wait(philo->dlist->s_dead);
	if (!philo->dlist->dead)
	{
		// pthread_mutex_unlock(&philo->dlist->m_dead);
		sem_post(philo->dlist->s_dead);

		// pthread_mutex_lock(&philo->dlist->ph_write);
		sem_wait(philo->dlist->ph_write);
		printf ("%ld\t%d\t%s\n", current_time() - philo->dlist->start_time, philo->index_ph, print);
		// pthread_mutex_unlock(&philo->dlist->ph_write);
		sem_post(philo->dlist->ph_write);
	}
	else
		// pthread_mutex_unlock(&philo->dlist->m_dead);
		sem_post(philo->dlist->s_dead);
}

void	philo_think(t_philo *philo)
{
	
	philo_write(philo, "is thinking");
	// pthread_mutex_lock(&philo->m_ph);
	sem_wait(philo->s_ph);
	if (philo->dlist->nbr_philo % 2 == 1)
	{
		if (philo->dlist->time_to_die - (philo->last_ate - current_time()) > philo->dlist->time_to_eat + 10)
		{
			// pthread_mutex_unlock(&philo->m_ph);
			sem_post(philo->s_ph);
			ft_msleep(philo->dlist->time_to_eat, philo);
		}
		else 
			// pthread_mutex_unlock(&philo->m_ph);
			sem_post(philo->s_ph);
	}
	else
		// pthread_mutex_unlock(&philo->m_ph);
		sem_post(philo->s_ph);
}

static void philo_eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->dlist->forks[dominant_fork]);
	sem_wait(philo->dlist->forks);
	philo_write(philo, "has taken a fork.F");
	// pthread_mutex_lock(&philo->dlist->forks[passive_fork]);
	sem_wait(philo->dlist->forks);
	philo_write(philo, "has taken a fork.S");
	// if (dominant_fork == passive_fork)
	// {
	// 	pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
	// 	return ;
	// }
	// pthread_mutex_lock(&philo->m_ph);
	sem_wait(philo->s_ph);
	philo->last_ate = current_time();
	// pthread_mutex_unlock(&philo->m_ph);
	sem_post(philo->s_ph);
	philo_write(philo, "is eating");
	ft_msleep(philo->dlist->time_to_eat, philo);
	// pthread_mutex_unlock(&philo->dlist->forks[dominant_fork]);
	// pthread_mutex_unlock(&philo->dlist->forks[passive_fork]);
	sem_post(philo->dlist->forks);
	sem_post(philo->dlist->forks);
}

static void	philo_do(t_philo *philo)
{
	int	times_ate;

	times_ate = 0;

	while (times_ate != philo->dlist->must_eat && is_dead(philo))
	{
		philo_think(philo);
		write (2, "BINGO\n", 7);
		philo_eat(philo);
		printf("p%d\tis running\n", philo->index_ph);
		times_ate++;
		if (times_ate != philo->dlist->must_eat)
		{
			philo_write(philo, "is sleeping");
			ft_msleep(philo->dlist->time_to_sleep, philo);
		}
	}
	// pthread_mutex_lock(&philo->m_ph);
	sem_wait(philo->s_ph);
	philo->finished = 1;
	// pthread_mutex_unlock(&philo->m_ph);
	sem_post(philo->s_ph);
}

void	*philo_action(void *arg)
{
	t_philo 		*philo;

	philo = (t_philo *)arg;
	// philo->s_ph = sem_open("s_ph", O_CREAT, 0777, 1);
	//     if (philo->s_ph == SEM_FAILED) {
    //     perror("sem_open");
    //     free(philo);
    //     exit(EXIT_FAILURE);
    // }
	// pthread_mutex_lock(&philo->m_ph);
	sem_wait(philo->s_ph);
	philo->last_ate = current_time();
	// pthread_mutex_unlock(&philo->m_ph);
	sem_post(philo->s_ph);
	philo_do(philo);
	// sem_close(philo->s_ph);
	// sem_unlink("/s_ph");
	return (NULL);
}
