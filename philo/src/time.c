/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 21:06:05 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 15:12:47 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	timestamp(t_data *data)
{
	return (get_time_ms() - data->start_time);
}

void	smart_sleep(t_data *data, long duration)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration)
	{
		if (get_stop(data))
			break ;
		usleep(100);
	}
}
