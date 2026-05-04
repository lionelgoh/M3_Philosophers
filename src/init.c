/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:33:44 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 22:28:00 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->stop_flag = 0;
	if (init_alloc_and_shared_mutexes(data) != 0)
		return (1);
	if (init_fork_mutexes(data) != 0)
		return (1);
	return (0);
}

int	init_alloc_and_shared_mutexes(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->rules.num_philo);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->rules.num_philo);
	if (!data->philos)
		return (free(data->forks), 1);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (free(data->forks), free(data->philos), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		return (free(data->forks), free(data->philos), 1);
	}
	return (0);
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->stop_mutex);
			free(data->forks);
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->rules.num_philo)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->last_meal_time = 0;
		philo->meals_eaten = 0;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->rules.num_philo];
		philo->data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			destroy_meal_mutexes(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}
