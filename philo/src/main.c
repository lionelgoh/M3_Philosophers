/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liogoh <liogoh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:15:25 by liogoh            #+#    #+#             */
/*   Updated: 2026/05/04 22:20:22 by liogoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_args(ac, av, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	if (init_philos(&data) != 0)
	{
		cleanup_shared(&data);
		return (1);
	}
	if (start_threads(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	join_threads(&data);
	cleanup(&data);
	return (0);
}

// int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void	*routine(void *arg)
// {
// 	int	index = *(int *)arg;
// 	printf("%d ", index);
// }

// int	main(int argc, char *argv[])
// {
// 	pthread_t	th[10];

// 	for (int i = 0; i < 10; i++)
// 	{
// 		if (pthread_create(&th[i], NULL, &routine, &i) != 0)
// 			perror("Failed to create thread\n");
// 	}
// 	for (int i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			perror("Failed to join thread\n");
// 	}
// 	return (0);
// }