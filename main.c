/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/01/22 20:59:25 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_args
{
	int	number_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_philo_must_eat;
}			t_args;

long	ft_atoi(const char *str)
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
		if (check_int[i[0]] <= -1
			||check_int[i[0]] < INT_MIN || check_int[i[0]] > INT_MAX)
			return (-1);
		i[1]++;
		i[0]++;
	}
	info->number_philos = check_int[0];
	info->time_to_die = check_int[1];
	info->time_to_eat = check_int[2];
	info->time_to_sleep = check_int[3];
	if (argc == 6)
		info->number_philo_must_eat = check_int[4];
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	info;

	if (argc != 5 && argc != 6)
		return (printf("Invalid amount of arguments\n"));
	if (get_input(argc, argv, &info) == -1)
		return (printf("Invalid input\n"));
	printf("%d %d %d %d %d\n", info.number_philos, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.number_philo_must_eat);
	return (0);
}
