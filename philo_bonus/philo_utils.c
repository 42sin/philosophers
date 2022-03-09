/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:07:36 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 00:40:57 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
