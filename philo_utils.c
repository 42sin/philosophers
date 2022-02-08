/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:07:36 by eozben            #+#    #+#             */
/*   Updated: 2022/02/08 19:47:45 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_philo *philo_arr, pthread_mutex_t *forks, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&forks[i--]);
	free(forks);
	free(philo_arr);
	return (-1);
}

int	free_structs(t_args *info)
{
	destroy_forks(info->philo_arr, info->forks, -1);
	return (-1);
}

time_t	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	ft_usleep(long ms)
{
	time_t	target;

	target = ft_gettimeofday() + ms;
	while (ft_gettimeofday() < target)
		usleep(500);
	return (1);
}

time_t	time_now(t_args *info)
{
	return (ft_gettimeofday() - info->sim_start);
}
