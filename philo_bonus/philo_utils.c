/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:07:36 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 17:27:09 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	processes(t_args *info, pid_t pid, int i)
{
	if (pid == 0)
	{
		info->philo.ph_id = i;
		if (pthread_create(&info->death_t, NULL, &reaper, (void *)info))
			return (destroy_sems(info));
		philo(&info->philo);
		pthread_join(info->death_t, NULL);
	}
	else
	{
		if (pid < 0)
			return (destroy_sems(info));
		i++;
	}
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
