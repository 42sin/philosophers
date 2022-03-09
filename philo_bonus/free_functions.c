/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:05:12 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 01:12:16 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	close_sem(sem_t *sem)
{
	if (sem != NULL && sem != SEM_FAILED)
		sem_close(sem);
	return (-1);
}

int	destroy_sems(t_args *info)
{
	close_sem(info->write);
	close_sem(info->death_lock);
	close_sem(info->meal_lock);
	close_sem(info->start_philos);
	close_sem(info->eat_protect);
	close_sem(info->forks);
	return (-1);
}

void	unlink_sems(void)
{
	sem_unlink("/write");
	sem_unlink("/death");
	sem_unlink("/meal");
	sem_unlink("/start");
	sem_unlink("/eat");
	sem_unlink("/forks");
}