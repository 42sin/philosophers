/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/03/08 17:02:13 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper(void *args)
{
	t_args	*info;
	int		i;

	info = (void *)args;
	while (1)
	{
		i = 0;
		while (i < info->num_philos)
		{
			pthread_mutex_lock(&info->meal_lock);
			pthread_mutex_lock(&info->eat_protect);
			if (check_if_philo_died(info, i))
				return (NULL);
			if (check_if_philo_ate(info))
				return (NULL);
			pthread_mutex_unlock(&info->meal_lock);
			pthread_mutex_unlock(&info->eat_protect);
			i++;
		}
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	if (check_death_lock(philo))
		return ;
	if (!check_death_lock(philo))
		do_routine(philo, -1, "thinking");
	if (!check_death_lock(philo) && philo->ph_id % 2 == 0)
		lock_forks(philo->right_fork, philo->left_fork, philo);
	else if (!check_death_lock(philo))
		lock_forks(philo->left_fork, philo->right_fork, philo);
	if (!check_death_lock(philo))
		do_routine(philo, philo->info->time_to_eat, "eating");
	drop_forks(philo->left_fork, philo->right_fork);
	if (!check_death_lock(philo))
		do_routine(philo, philo->info->time_to_sleep, "sleeping");
}

void	*philo(void *philo_struct)
{
	t_philo	*philo;

	philo = (void *)philo_struct;
	pthread_mutex_lock(&philo->info->start_philos);
	pthread_mutex_unlock(&philo->info->start_philos);
	if (philo->ph_id % 2 == 1)
		ft_usleep(philo->info->time_to_eat);
	while (!check_death_lock(philo))
		philo_routine(philo);
	return (NULL);
}

int	start_threads(t_args *info)
{
	int	i;

	i = 0;
	if (info->number_philo_must_eat == 0)
		return (0);
	pthread_mutex_lock(&info->start_philos);
	while (i < info->num_philos)
	{
		if (pthread_create(&info->philo_arr[i].tid, NULL, &philo,
				(void *)&info->philo_arr[i]))
			return (-1);
		i++;
	}
	pthread_mutex_unlock(&info->start_philos);
	if (pthread_create(&info->death_t, NULL, &reaper, (void *)info))
		return (-1);
	i = 0;
	while (i < info->num_philos)
		pthread_join(info->philo_arr[i++].tid, NULL);
	pthread_join(info->death_t, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	info;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of arguments\n"));
	if (get_input(argc, argv, &info) == -1)
		return (printf("Invalid input\n"));
	if (create_philos(&info) == -1)
		return (printf("Malloc Error occured\n"));
	if (init_philos(&info) == -1)
		return (printf("Initialization Error occured\n"));
	info.sim_start = ft_gettimeofday();
	if (start_threads(&info) == -1)
		return (printf("Runtime Error\n"));
	free_structs(&info);
	return (0);
}
