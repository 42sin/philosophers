/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 00:46:31 by eozben            #+#    #+#             */
/*   Updated: 2022/02/01 01:11:45 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_mutex *write_protect, int philo_number)
{
	pthread_mutex_lock(write_protect);
	printf("%ld %d has taken a fork\n", ft_gettimeofday(), philo_number);
	pthread_mutex_unlock(write_protect);
}

void	lock_forks(t_mutex *r_fork, t_mutex *l_fork, int ph_id, t_mutex *write)
{
	pthread_mutex_lock(r_fork);
	grab_fork(write, ph_id + 1);
	pthread_mutex_lock(l_fork);
	grab_fork(write, ph_id + 1);
}

void	eat_routine(t_mutex *write_protect, int ph_id, int eat_time)
{
	pthread_mutex_lock(write_protect);
	printf("%ld %d is eating\n", ft_gettimeofday(), ph_id + 1);
	pthread_mutex_unlock(write_protect);
	ft_usleep(eat_time);
}

void	drop_forks(t_mutex *l_fork, t_mutex *r_fork)
{
	pthread_mutex_unlock(r_fork);
	pthread_mutex_unlock(l_fork);
}

void	sleep_routine(t_mutex *write_protect, int ph_id, int sleep_time)
{
	pthread_mutex_lock(write_protect);
	printf("%ld %d is sleeping\n", ft_gettimeofday(), ph_id + 1);
	pthread_mutex_unlock(write_protect);
	ft_usleep(sleep_time);
}

void	think_routine(t_mutex *write_protect, int ph_id)
{
	pthread_mutex_lock(write_protect);
	printf("%ld %d is thinking\n", ft_gettimeofday(), ph_id + 1);
	pthread_mutex_unlock(write_protect);
}