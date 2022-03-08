/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:05:12 by eozben            #+#    #+#             */
/*   Updated: 2022/03/08 21:28:55 by eozben           ###   ########.fr       */
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

int	destroy_threads(t_args *info, int i)
{
	pthread_mutex_lock(&info->death_lock);
	info->death_occured = 1;
	pthread_mutex_unlock(&info->start_philos);
	pthread_mutex_unlock(&info->death_lock);
	while (i >= 0)
		pthread_join(info->philo_arr[i--].tid, NULL);
	pthread_join(info->death_t, NULL);
	return (destroy_forks(info->philo_arr, info->forks,
			info->num_philos - 1));
}
