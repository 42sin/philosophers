/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:03:21 by eozben            #+#    #+#             */
/*   Updated: 2022/02/08 19:56:36 by eozben           ###   ########.fr       */
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

int	init_mutex(t_args *info, t_philo *philo_array, t_mutex *forks, int i)
{
	if (pthread_mutex_init(&info->write_protect, NULL))
		return (destroy_forks(philo_array, forks, i));
	if (pthread_mutex_init(&info->death_lock, NULL))
		return (destroy_forks(philo_array, forks, i));
	if (pthread_mutex_init(&info->meal_lock, NULL))
		return (destroy_forks(philo_array, forks, i));
	if (pthread_mutex_init(&info->start_philos, NULL))
		return (destroy_forks(philo_array, forks, i));
	if (pthread_mutex_init(&info->eat_protect, NULL))
		return (destroy_forks(philo_array, forks, i));
}

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
	if (init_mutex(info, philo_array, forks, i) == -1)
		return (-1);
	info->forks = forks;
	info->philo_arr = philo_array;
	return (0);
}

int	init_philos(t_args *info)
{
	int	i;

	i = 0;
	info->death_occured = 0;
	info->global_eat_count = 0;
	while (i < info->num_philos)
	{
		info->philo_arr[i].right_fork = &info->forks[i];
		info->philo_arr[i].left_fork = &info->forks[(i + 1) % info->num_philos];
		info->philo_arr[i].ph_id = i;
		info->philo_arr[i].info = info;
		info->philo_arr[i].last_meal = 0;
		info->philo_arr[i].eat_count = 0;
		i++;
	}
	return (0);
}
