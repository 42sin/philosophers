/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 00:46:31 by eozben            #+#    #+#             */
/*   Updated: 2022/02/08 19:54:20 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if (!check_death_lock(philo))
	{
		pthread_mutex_lock(&philo->info->write_protect);
		if (!check_death_lock(philo))
			printf("%ld %d has taken a fork\n",
				time_now(philo->info), philo->ph_id + 1);
		pthread_mutex_unlock(&philo->info->write_protect);
	}
}

int	drop_forks(t_mutex *l_fork, t_mutex *r_fork)
{
	if (r_fork != NULL)
		pthread_mutex_unlock(r_fork);
	if (l_fork != NULL)
		pthread_mutex_unlock(l_fork);
	return (1);
}

int	lock_forks(t_mutex *first_fork, t_mutex *second_fork, t_philo *philo)
{
	if (!check_death_lock(philo))
		pthread_mutex_lock(first_fork);
	take_fork(philo);
	if (check_death_lock(philo))
		return (drop_forks(first_fork, NULL));
	if (!check_death_lock(philo))
	{
		if (first_fork == second_fork)
			return (ft_usleep(philo->info->time_to_die + 50));
		pthread_mutex_lock(second_fork);
	}
	take_fork(philo);
	if (check_death_lock(philo))
		return (drop_forks(first_fork, second_fork));
	return (0);
}

void	increment_eat_count(t_philo *philo, char *to_do)
{
	if (to_do[0] == 'e' && philo->info->number_philo_must_eat != -1
		&& !check_death_lock(philo))
	{
		pthread_mutex_lock(&philo->info->eat_protect);
		philo->eat_count += 1;
		if (philo->eat_count == philo->info->number_philo_must_eat)
			philo->info->global_eat_count += 1;
		pthread_mutex_unlock(&philo->info->eat_protect);
	}
}

void	update_last_meal(t_philo *philo, char *to_do)
{
	if (to_do[0] == 'e')
	{
		if (!check_death_lock(philo))
		{
			pthread_mutex_lock(&philo->info->meal_lock);
			philo->last_meal = ft_gettimeofday() - philo->info->sim_start;
			pthread_mutex_unlock(&philo->info->meal_lock);
		}
	}
}

void	do_routine(t_philo *philo, int time, char *to_do)
{
	if (check_death_lock(philo))
		return ;
	if (!check_death_lock(philo))
	{
		pthread_mutex_lock(&philo->info->write_protect);
		if (!check_death_lock(philo))
			printf("%ld %d is %s\n", ft_gettimeofday() - philo->info->sim_start,
				philo->ph_id + 1, to_do);
		pthread_mutex_unlock(&philo->info->write_protect);
	}
	if (!check_death_lock(philo) && time != -1)
	{
		update_last_meal(philo, to_do);
		if (!check_death_lock(philo) && time != -1)
			ft_usleep(time);
		increment_eat_count(philo, to_do);
	}
}
