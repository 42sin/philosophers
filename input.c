/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:03:21 by eozben            #+#    #+#             */
/*   Updated: 2022/01/31 19:28:46 by eozben           ###   ########.fr       */
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
	return (0);
}
