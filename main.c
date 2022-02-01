/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/02/01 01:17:35 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_args *info)
{
	t_philo			*philo_array;
	pthread_mutex_t	*forks;
	int				i;

	philo_array = malloc(sizeof(t_philo) * info->num_philos);
	if (!philo_array)
		return (-1);
	forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!forks)
	{
		free(philo_array);
		return (-1);
	}
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (destroy_forks(philo_array, forks, i));
	}
	if (pthread_mutex_init(&info->write_protect, NULL))
		return (destroy_forks(philo_array, forks, i));
	info->forks = forks;
	info->philo_arr = philo_array;
	return (0);
}

int	init_philos(t_args *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		info->philo_arr[i].right_fork = &info->forks[i];
		info->philo_arr[i].left_fork = &info->forks[(i + 1) % info->num_philos];
		info->philo_arr[i].ph_id = i;
		info->philo_arr[i].info = info;
		i++;
	}
	return (0);
}

void	philo_routine(t_philo *philo, int philo_num)
{
	while (true)
	{
		if (philo_num % 2 == 0)
			lock_forks(philo->right_fork, philo->left_fork, philo_num,
				&args_->write_protect);
		else
			lock_forks(philo->left_fork, philo->right_fork, philo_num,
				&args_->write_protect);
		eat_routine(&args_->write_protect, philo_num, args_->time_to_eat);
		drop_forks(philo->left_fork, philo->right_fork);
		sleep_routine(&args_->write_protect, philo_num, args_->time_to_sleep);
		think_routine(&args_->write_protect, philo_num);
	}
}

void	*philo(void *philo_struct)
{
	t_philo	*philo;

	philo = (void *)philo_struct;
	philo_routine(philo, philo->ph_id);
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
	if (start_threads(&info) == -1)
		return (printf("Runtime Error\n"));
	free_structs(&info);
	return (0);
}
