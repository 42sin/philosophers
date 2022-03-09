/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 00:46:31 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 00:27:59 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (!check_death_lock(philo))
	{
		sem_wait(philo->info->write);
		if (!check_death_lock(philo))
			printf("%ld %d has taken a fork\n",
				time_now(philo->info), philo->ph_id + 1);
		sem_post(philo->info->write);
	}
}

int	lock_forks(t_philo *philo)
{
	if (!check_death_lock(philo))
		sem_wait(philo->info->forks);
	take_fork(philo);
	if (check_death_lock(philo))
		return (sem_post(philo->info->forks));
	if (!check_death_lock(philo))
		sem_wait(philo->info->forks);
	take_fork(philo);
	if (check_death_lock(philo))
		return (2);
	return (1);
}

void	increment_eat_count(t_philo *philo, char *to_do)
{
	if (to_do[0] == 'e' && philo->info->number_philo_must_eat != -1
		&& !check_death_lock(philo))
	{
		sem_wait(philo->info->eat_protect);
		philo->eat_count += 1;
		if (philo->eat_count == philo->info->number_philo_must_eat)
			philo->info->global_eat_count += 1;
		sem_post(philo->info->eat_protect);
	}
}

void	update_last_meal(t_philo *philo, char *to_do)
{
	if (to_do[0] == 'e')
	{
		if (!check_death_lock(philo))
		{
			sem_wait(philo->info->meal_lock);
			philo->last_meal = ft_gettimeofday() - philo->info->sim_start;
			sem_post(philo->info->meal_lock);
		}
	}
}

void	do_routine(t_philo *philo, int time, char *to_do)
{
	if (check_death_lock(philo))
		return ;
	if (!check_death_lock(philo))
	{
		sem_wait(philo->info->write);
		if (!check_death_lock(philo))
			printf("%ld %d is %s\n", ft_gettimeofday() - philo->info->sim_start,
				philo->ph_id + 1, to_do);
		sem_post(philo->info->write);
	}
	if (!check_death_lock(philo) && time != -1)
	{
		update_last_meal(philo, to_do);
		if (!check_death_lock(philo) && time != -1)
			ft_usleep(time);
		increment_eat_count(philo, to_do);
	}
}
