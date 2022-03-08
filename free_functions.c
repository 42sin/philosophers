/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:05:12 by eozben            #+#    #+#             */
/*   Updated: 2022/03/08 17:05:47 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_philo *philo_arr, pthread_mutex_t *forks, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&forks[i--]);
	free(forks);
	free(philo_arr);
	return (-1);
}

int	free_structs(t_args *info)
{
	destroy_forks(info->philo_arr, info->forks, -1);
	return (-1);
}
