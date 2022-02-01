/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:07:36 by eozben            #+#    #+#             */
/*   Updated: 2022/01/31 23:46:10 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
	destroy_forks(info->philo_arr, info->forks, 0);
	return (-1);
}

long	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	ft_usleep(long ms)
{
	long	target;

	target = ft_gettimeofday() + ms;
	while (ft_gettimeofday() < target)
		usleep(50);
	return (0);
}
