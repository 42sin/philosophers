/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:00:44 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 00:10:44 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_lock(t_philo *philo)
{
	sem_wait(philo->info->death_lock);
	if (philo->info->death_occured == 0)
	{
		sem_post(philo->info->death_lock);
		return (0);
	}
	sem_post(philo->info->death_lock);
	return (1);
}

int	check_if_philo_died(t_args *info)
{
	if (info->philo->last_meal + info->time_to_die < time_now(info))
	{
		sem_post(info->meal_lock);
		sem_wait(info->death_lock);
		info->death_occured = 1;
		sem_post(info->death_lock);
		sem_wait(info->write);
		printf("%ld %d died\n", time_now(info), info->philo->ph_id + 1);
		sem_post(info->write);
		sem_post(info->eat_protect);
		return (1);
	}
	return (0);
}

int	check_if_philo_ate(t_args *info)
{
	if (info->global_eat_count >= info->num_philos
		&& info->number_philo_must_eat != -1)
	{
		sem_post(info->meal_lock);
		sem_post(info->eat_protect);
		sem_wait(info->death_lock);
		info->death_occured = 1;
		sem_post(info->death_lock);
		return (1);
	}
	return (0);
}
