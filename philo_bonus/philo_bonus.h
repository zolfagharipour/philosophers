/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:38:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/15 17:54:12 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define ALIVE -1
# define FINISHED -2
# define TOO_FEW 6
# define TOO_MANY 7
# define TOO_MANY_PHILO 8

typedef struct s_philo
{
	sem_t		*forks;
	sem_t		*s_dead;
	sem_t		*ph_write;
	sem_t		*s_ph;
	pid_t		pid[500];
	int			index_ph;
	long int	last_ate;
	int			nbr_philo;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int			must_eat;
	long int	start_time;
}	t_philo;

int			ft_atoi(const char *nptr);
int			forking(t_philo *philo);
void		philo_action(t_philo *philo);
long int	current_time(void);
void		ft_msleep(long int usec, t_philo *philo);
int			massacre_children(t_philo *philo);
void		*monitor(void *arg);


#endif