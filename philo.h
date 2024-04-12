/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:56 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/12 17:25:21 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define ALIVE -1
# define FINISHED -2
# define TOO_FEW 6
# define TOO_MANY 7

typedef struct s_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	ph_write;
	int				nbr_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat;
	int				dead;
	long int		start_time;
}	t_info;

typedef struct s_philo
{
	pthread_mutex_t	m_ph;
	struct s_info	*dlist;
	int				index_ph;
	long int		last_ate;
	long int		finished;
}	t_philo;

int			ft_atoi(const char *nptr);
pthread_t	*threading(t_info *philo);
void		*philo_action(void *arg);
void		*supervisor(void *arg);
long int	current_time(void);
void		ft_msleep(long int usec, t_philo *philo);
int			is_dead(t_philo *philo);
void		philo_write(t_philo *philo, char *print);

#endif