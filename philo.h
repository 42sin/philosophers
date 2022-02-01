/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:16 by eozben            #+#    #+#             */
/*   Updated: 2022/02/01 01:02:35 by eozben           ###   ########.fr       */
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
# include <stdbool.h>

# define args_ philo->info

typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_philo_must_eat;
	t_mutex			*forks;
	t_philo			*philo_arr;
	t_mutex			write_protect;
}			t_args;

struct s_philo
{
	int				ph_id;
	pthread_t		tid;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_args			*info;
	int				status;
};

int		get_input(int argc, char **argv, t_args *info);
int		ft_usleep(long ms);
int		free_structs(t_args *info);
int		destroy_forks(t_philo *philo_arr, pthread_mutex_t *forks, int i);
int		ft_strlen(char *str);
long	ft_gettimeofday(void);
void	grab_fork(t_mutex *write_protect, int philo_number);
void	lock_forks(t_mutex *r_fork, t_mutex *l_fork, int ph_id, t_mutex *write);
void	eat_routine(t_mutex *write_protect, int ph_id, int eat_time);
void	drop_forks(t_mutex *l_fork, t_mutex *r_fork);
void	sleep_routine(t_mutex *write_protect, int ph_id, int sleep_time);
void	think_routine(t_mutex *write_protect, int ph_id);

#endif