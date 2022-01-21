/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/01/22 00:04:34 by eozben           ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	sign = 1;
	result = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

//rewrite ft_atoi with protections
int	get_input(int argc, char **argv, t_args *info)
{
	info->number_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_philo_must_eat = ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	info;

	if (argc != 5 && argc != 6)
		return (-1);
	if (get_input(argc, argv, &info) == -1)
		return (-1);
	return (0);
}
