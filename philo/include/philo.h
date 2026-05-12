/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:15:14 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/12 14:57:20 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_rules
{
	int		num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat_count;
}	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_rules			rules;
	long			start_time;
	int				stop_flag;
	pthread_t		monitor_thread;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		ft_atoi_positive(char *str);
int		parse_args(int ac, char **av, t_data *data);
int		init_data(t_data *data);
int		init_alloc_and_shared_mutexes(t_data *data);
int		init_fork_mutexes(t_data *data);
int		init_philos(t_data *data);
long	get_time_ms(void);
long	timestamp(t_data *data);
void	smart_sleep(t_data *data, long duration);
int		get_stop(t_data *data);
void	set_stop(t_data *data, int value);
void	print_state(t_philo *philo, char *msg);
int		is_dead(t_philo *philo);
void	print_death(t_philo *philo);
int		start_threads(t_data *data);
int		join_threads(t_data *data);
void	join_created_threads(t_data *data, int count);
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
int		all_ate_enough(t_data *data);
void	*monitor_routine(void *arg);

void	cleanup(t_data *data);
void	cleanup_shared(t_data *data);
void	destroy_meal_mutexes(t_data *data, int count);
#endif