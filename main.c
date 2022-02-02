/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/02/02 02:49:25 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo)
{
	do_routine(philo, -1, "thinking");
	if (philo->ph_id % 2 == 0)
		lock_forks(philo->right_fork, philo->left_fork, philo);
	else
		lock_forks(philo->left_fork, philo->right_fork, philo);
	do_routine(philo, philo->info->time_to_eat, "eating");
	drop_forks(philo->left_fork, philo->right_fork);
	do_routine(philo, philo->info->time_to_sleep, "sleeping");
}

void	*philo(void *philo_struct)
{
	t_philo	*philo;

	philo = (void *)philo_struct;
	while (philo->info->death_occured == 'a')
		philo_routine(philo);
	return (NULL);
}

int	start_threads(t_args *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_create(&info->philo_arr[i].tid, NULL, &philo, (void *)&info->philo_arr[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < info->num_philos)
		pthread_join(info->philo_arr[i++].tid, NULL);
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
