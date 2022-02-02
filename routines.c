/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 00:46:31 by eozben            #+#    #+#             */
/*   Updated: 2022/02/02 02:49:57 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_mutex *first_fork, t_mutex *second_fork, t_philo *philo)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&philo->info->write_protect);
	printf("%ld %d has taken a fork\n",
		ft_gettimeofday() - philo->info->sim_start, philo->ph_id + 1);
	pthread_mutex_unlock(&philo->info->write_protect);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&philo->info->write_protect);
	printf("%ld %d has taken a fork\n",
		ft_gettimeofday() - philo->info->sim_start, philo->ph_id + 1);
	pthread_mutex_unlock(&philo->info->write_protect);
}

void	drop_forks(t_mutex *l_fork, t_mutex *r_fork)
{
	pthread_mutex_unlock(r_fork);
	pthread_mutex_unlock(l_fork);
}

void	do_routine(t_philo *philo, int time, char *to_do)
{
	pthread_mutex_lock(&philo->info->write_protect);
	printf("%ld %d is %s\n", ft_gettimeofday() - philo->info->sim_start,
		philo->ph_id + 1, to_do);
	pthread_mutex_unlock(&philo->info->write_protect);
	if (time != -1)
		ft_usleep(time);
}
