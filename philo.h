/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:16 by eozben            #+#    #+#             */
/*   Updated: 2022/01/24 00:19:57 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

typedef struct s_args
{
	int	number_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_philo_must_eat;
}			t_args;

typedef struct s_philo
{
	pthread_t		tid;
	char			status;
}			t_philo;

typedef struct s_waiter
{

}				t_waiter;

int	get_input(int argc, char **argv, t_args *info);
int	ft_usleep(long ms);

#endif