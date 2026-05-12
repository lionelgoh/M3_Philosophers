/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:55:27 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 22:19:16 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	destroy_meal_mutexes(data, data->rules.num_philo);
	cleanup_shared(data);
}

void	cleanup_shared(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->forks);
	free(data->philos);
}

void	destroy_meal_mutexes(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
}
