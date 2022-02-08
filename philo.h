/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:16 by eozben            #+#    #+#             */
/*   Updated: 2022/02/08 19:47:53 by eozben           ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	pthread_t		death_t;
	bool			death_occured;
	int				time_to_sleep;
	t_mutex			death_lock;
	t_mutex			meal_lock;
	t_mutex			start_philos;
	int				global_eat_count;
	int				number_philo_must_eat;
	time_t			sim_start;
	t_mutex			*forks;
	t_mutex			eat_protect;
	t_philo			*philo_arr;
	t_mutex			write_protect;
}			t_args;

struct s_philo
{
	int				ph_id;
	int				eat_count;
	pthread_t		tid;
	time_t			last_meal;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_args			*info;
};

int		get_input(int argc, char **argv, t_args *info);
int		ft_usleep(long ms);
int		free_structs(t_args *info);
int		init_philos(t_args *info);
int		destroy_forks(t_philo *philo_arr, pthread_mutex_t *forks, int i);
int		lock_forks(t_mutex *first_fork, t_mutex *second_fork, t_philo *philo);
int		drop_forks(t_mutex *l_fork, t_mutex *r_fork);
void	do_routine(t_philo *philo, int time, char *to_do);
int		create_philos(t_args *info);
time_t	ft_gettimeofday(void);
int		check_death_lock(t_philo *philo);
time_t	time_now(t_args *info);

#endif