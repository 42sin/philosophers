/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:05:16 by eozben            #+#    #+#             */
/*   Updated: 2022/03/09 17:26:22 by eozben           ###   ########.fr       */
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
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

struct s_philo
{
	int				ph_id;
	int				eat_count;
	time_t			last_meal;
	t_args			*info;
};

struct s_args
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	pthread_t		death_t;
	sem_t			*write;
	sem_t			*death_lock;
	sem_t			*meal_lock;
	sem_t			*start_philos;
	sem_t			*eat_protect;
	sem_t			*forks;
	sem_t			*eat_sem;
	bool			death_occured;
	int				time_to_sleep;
	int				global_eat_count;
	int				number_philo_must_eat;
	time_t			sim_start;
	t_philo			philo;
};

int		get_input(int argc, char **argv, t_args *info);
int		ft_usleep(long ms);
int		free_structs(t_args *info);
void	do_routine(t_philo *philo, int time, char *to_do);
int		create_philos(t_args *info);
time_t	ft_gettimeofday(void);
int		check_death_lock(t_philo *philo);
time_t	time_now(t_args *info);
int		check_if_philo_ate(t_args *info);
int		check_if_philo_died(t_args *info);
int		destroy_threads(t_args *info, int i);
int		init_sems(t_args *info);
int		destroy_sems(t_args *info);
int		close_sem(sem_t *sem);
void	unlink_sems(void);
int		lock_forks(t_philo *philo);
void	check_eat(t_args *info);

#endif