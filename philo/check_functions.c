/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:00:44 by eozben            #+#    #+#             */
/*   Updated: 2022/03/08 17:01:26 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_lock);
	if (philo->info->death_occured == 0)
	{
		pthread_mutex_unlock(&philo->info->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	return (1);
}

int	check_if_philo_died(t_args *info, int i)
{
	if (info->philo_arr[i].last_meal + info->time_to_die < time_now(info))
	{
		pthread_mutex_unlock(&info->meal_lock);
		pthread_mutex_lock(&info->death_lock);
		info->death_occured = 1;
		pthread_mutex_unlock(&info->death_lock);
		pthread_mutex_lock(&info->write_protect);
		printf("%ld %d died\n", time_now(info), info->philo_arr[i].ph_id + 1);
		pthread_mutex_unlock(&info->write_protect);
		pthread_mutex_unlock(&info->eat_protect);
		return (1);
	}
	return (0);
}

int	check_if_philo_ate(t_args *info)
{
	if (info->global_eat_count >= info->num_philos
		&& info->number_philo_must_eat != -1)
	{
		pthread_mutex_unlock(&info->meal_lock);
		pthread_mutex_unlock(&info->eat_protect);
		pthread_mutex_lock(&info->death_lock);
		info->death_occured = 1;
		pthread_mutex_unlock(&info->death_lock);
		return (1);
	}
	return (0);
}
