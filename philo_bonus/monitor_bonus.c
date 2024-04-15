/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:39:04 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/04/15 18:02:54 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    while(1)
    {
        sem_wait(philo->s_ph);
        if (current_time() - philo->last_ate > philo->time_to_die - 1)
        {
            sem_post(philo->s_ph);
            sem_wait(philo->ph_write);
            printf ("\x1b[31m%ld %d is dead.\x1b[0m\n",
                current_time() - philo->start_time, philo->index_ph + 1);
            sem_post(philo->ph_write);
            sem_close(philo->s_ph);
            sem_unlink("s_ph");
            sem_post(philo->s_dead);
            exit(EXIT_FAILURE);
        }
        else
        {
            sem_post(philo->s_ph);
            usleep (100);	
        }
    }
	return (NULL);
}