/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:03:21 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 17:11:20 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	int		j;

	sign = 1;
	result = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (j == i || str[i] != '\0')
		return (-1);
	return (result * sign);
}

int	get_input(int argc, char **argv, t_args *info)
{
	long	check_int[5];
	int		i[2];

	i[0] = 0;
	i[1] = 1;
	while (i[0] < argc - 1)
	{
		check_int[i[0]] = ft_atoi(argv[i[1]]);
		if (check_int[i[0]] <= -1 || check_int[0] == 0
			|| check_int[i[0]] < INT_MIN || check_int[i[0]] > INT_MAX)
			return (-1);
		i[1]++;
		i[0]++;
	}
	info->num_philos = check_int[0];
	info->time_to_die = check_int[1];
	info->time_to_eat = check_int[2];
	info->time_to_sleep = check_int[3];
	if (argc == 6)
		info->number_philo_must_eat = check_int[4];
	else
		info->number_philo_must_eat = -1;
	return (0);
}

int	init_sems(t_args *info)
{
	unlink_sems();
	info->write = sem_open("/write", O_CREAT, 0700, 1);
	if (info->write == SEM_FAILED)
		return (-1);
	info->death_lock = sem_open("/death", O_CREAT, 0700, 1);
	if (info->death_lock == SEM_FAILED)
		return (close_sem(info->write));
	info->meal_lock = sem_open("/meal", O_CREAT, 0700, 1);
	if (info->meal_lock == SEM_FAILED)
		return (destroy_sems(info));
	info->start_philos = sem_open("/start", O_CREAT, 0700, 0);
	if (info->start_philos == SEM_FAILED)
		return (destroy_sems(info));
	info->eat_protect = sem_open("/eat", O_CREAT, 0700, 1);
	if (info->eat_protect == SEM_FAILED)
		return (destroy_sems(info));
	info->forks = sem_open("/forks", O_CREAT, 0700, info->num_philos);
	if (info->forks == SEM_FAILED)
		return (destroy_sems(info));
	info->eat_sem = sem_open("/eatcount", O_CREAT, 0700, 0);
	if (info->eat_sem == SEM_FAILED)
		return (destroy_sems(info));
	return (0);
}

int	create_philos(t_args *info)
{
	t_philo	philo;

	philo.info = info;
	philo.eat_count = 0;
	philo.ph_id = 0;
	philo.last_meal = 0;
	info->philo = philo;
	info->death_occured = 0;
	info->global_eat_count = 0;
	info->write = NULL;
	info->death_lock = NULL;
	info->meal_lock = NULL;
	info->start_philos = NULL;
	info->eat_sem = NULL;
	info->eat_protect = NULL;
	info->forks = NULL;
	return (0);
}
