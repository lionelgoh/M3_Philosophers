/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:59:53 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 19:00:30 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!get_stop(data))
	{
		i = 0;
		while (i < data->rules.num_philo)
		{
			if (is_dead(&data->philos[i]))
			{
				print_death(&data->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(data))
		{
			set_stop(data, 1);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	all_ate_enough(t_data *data)
{
	int	i;
	int	meals_eaten;

	if (data->rules.must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->rules.num_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		meals_eaten = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (meals_eaten < data->rules.must_eat_count)
			return (0);
		i++;
	}
	return (1);
}
