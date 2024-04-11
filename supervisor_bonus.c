#include "philo_bonus.h"

static int	check_philo(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	usleep(50 * philo->dlist->nbr_philo);
	while (i < philo->dlist->nbr_philo)
	{
		// pthread_mutex_lock(&philo[i].m_ph);
		sem_wait(philo[i].s_ph);
		if (current_time() - philo[i].last_ate > philo->dlist->time_to_die
			&& !philo[i].finished)
		{
			// pthread_mutex_lock(&philo[i].dlist->m_dead);
			sem_wait(philo[i].dlist->s_dead);
			philo->dlist->dead = 1;
			// pthread_mutex_unlock(&philo[i].dlist->m_dead);
			sem_post(philo[i].dlist->s_dead);
			// pthread_mutex_unlock(&philo[i].m_ph);
			sem_post(philo[i].s_ph);
			return (i);
		}
		else
			// pthread_mutex_unlock(&philo[i].m_ph);
			sem_post(philo[i].s_ph);
		// pthread_mutex_lock(&philo[i].m_ph);
		sem_wait(philo[i].s_ph);
		if (philo[i].finished)
			finished++;
		// pthread_mutex_unlock(&philo[i].m_ph);
		sem_post(philo[i].s_ph);
		i++;
	}
	if (finished == philo->dlist->nbr_philo)
		return (FINISHED);
	return (ALIVE);
}


void	*supervisor(void *arg)
{
	t_philo *philo;
	int		check;

	philo = (t_philo *)arg;
	check = ALIVE;
	while (check == ALIVE)
	{
		check = check_philo(philo);
	}
	if (check > ALIVE)
	{
		// pthread_mutex_lock(&philo->dlist->ph_write);
		sem_wait(philo->dlist->ph_write);
		printf ("\x1b[31m%ld %d is dead.\x1b[0m\n", current_time() - philo[0].dlist->start_time, check);
		// pthread_mutex_unlock(&philo->dlist->ph_write);
		sem_post(philo->dlist->ph_write);
	}
	return (NULL);
}
