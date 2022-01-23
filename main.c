/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:14 by eozben            #+#    #+#             */
/*   Updated: 2022/01/24 00:22:34 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_args *info)
{
	t_philo			*philo_array;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_protect;
	int				i;

	philo_array = malloc(sizeof(t_philo) * info->number_philos + 1);
	if (!philo_array)
		return (-1);
	forks = malloc(sizeof(pthread_mutex_t) * info->number_philos);
	if (!forks)
	{
		free(philo_array);
		return (-1);
	}
	i = 0;
	while (i < info->number_philos)
		pthread_mutex_init(&forks[i++], NULL);
	pthread_mutex_init(&write_protect, NULL);
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
	return (0);
}
