/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:53:35 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/03 20:35:47 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ft_atoi_positive(char *str)
{
	int		i;
	long	res;
	int		digit;

	i = 0;
	res = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		digit = str[i] - '0';
		if (res > (INT_MAX - digit) / 10)
			return (-1);
		res = res * 10 + digit;
		i++;
	}
	return ((int)res);
}

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [must_eat_count]\n");
		return (1);
	}
	data->rules.num_philo = ft_atoi_positive(av[1]);
	data->rules.time_to_die = ft_atoi_positive(av[2]);
	data->rules.time_to_eat = ft_atoi_positive(av[3]);
	data->rules.time_to_sleep = ft_atoi_positive(av[4]);
	if (ac == 6)
		data->rules.must_eat_count = ft_atoi_positive(av[5]);
	else
		data->rules.must_eat_count = -1;
	if (data->rules.num_philo <= 0
		|| data->rules.time_to_die <= 0
		|| data->rules.time_to_eat <= 0
		|| data->rules.time_to_sleep <= 0
		|| (ac == 6 && data->rules.must_eat_count <= 0))
	{
		printf("Error: arguments must be positive integers\n");
		return (1);
	}
	return (0);
}
