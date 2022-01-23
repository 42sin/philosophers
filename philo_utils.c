/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:07:36 by eozben            #+#    #+#             */
/*   Updated: 2022/01/23 23:48:32 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000000 + time.tv_usec));
}

int	ft_usleep(long ms)
{
	long	target;

	target = ft_gettimeofday() + (ms * 1000);
	while (ft_gettimeofday() < target)
		usleep(50);
	return (0);
}
