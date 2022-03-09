/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 17:27:02 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper(void *args)
{
	t_args	*info;

	info = (void *)args;
	while (1)
	{
		sem_wait(info->meal_lock);
		sem_wait(info->eat_protect);
		if (check_if_philo_died(info))
			return (NULL);
		sem_post(info->meal_lock);
		sem_post(info->eat_protect);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	if (check_death_lock(philo))
		return ;
	if (!check_death_lock(philo))
		do_routine(philo, -1, "thinking");
	if (!check_death_lock(philo))
	{
		if (lock_forks(philo) == 2)
		{
			sem_post(philo->info->forks);
			sem_post(philo->info->forks);
		}
	}
	if (!check_death_lock(philo))
		do_routine(philo, philo->info->time_to_eat, "eating");
	if (!check_death_lock(philo))
	{
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
	}
	if (!check_death_lock(philo))
		do_routine(philo, philo->info->time_to_sleep, "sleeping");
}

void	philo(t_philo *philo)
{
	if (check_death_lock(philo))
		return ;
	sem_wait(philo->info->start_philos);
	sem_post(philo->info->start_philos);
	if (!check_death_lock(philo) && philo->ph_id % 2 == 1)
		ft_usleep(philo->info->time_to_eat);
	while (!check_death_lock(philo))
		philo_routine(philo);
	return ;
}

int	start_philos(t_args *info)
{
	int		i;
	pid_t	pid;

	if (info->number_philo_must_eat == 0)
		return (0);
	pid = 1;
	i = 0;
	while (i < info->num_philos)
	{
		if (pid != 0)
			pid = fork();
		processes(info, pid, i);
	}
	if (pid != 0)
	{
		sem_post(info->start_philos);
		check_eat(info);
		waitpid(-1, NULL, 0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	info;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of arguments\n"));
	if (get_input(argc, argv, &info) == -1)
		return (printf("Invalid input\n"));
	create_philos(&info);
	if (init_sems(&info) == -1)
		return (printf("Semaphores could not be initialized\n"));
	info.sim_start = ft_gettimeofday();
	if (start_philos(&info) == -1)
		return (printf("Runtime Error\n"));
	destroy_sems(&info);
	unlink_sems();
	return (0);
}
