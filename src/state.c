/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 23:00:51 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 18:45:15 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_stop(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->stop_mutex);
	value = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (value);
}

void	set_stop(t_data *data, int value)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = value;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!get_stop(philo->data))
	{
		printf("%ld %d %s\n", timestamp(philo->data), philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_dead(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	time_since_meal = get_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_meal > philo->data->rules.time_to_die)
		return (1);
	return (0);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop_flag)
	{
		printf("%ld %d died\n", timestamp(philo->data), philo->id);
		philo->data->stop_flag = 1;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
