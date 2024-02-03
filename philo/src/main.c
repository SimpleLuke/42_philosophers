/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:36 by llai              #+#    #+#             */
/*   Updated: 2024/02/03 17:28:38 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	

	if (argc < 5)
	{
		print_err("Invalid arguments",
				"./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]");
		return (EXIT_FAILURE);
	}
	init_table(&table, argc, argv);
	start_simulation(&table);
	// printf("START: %lld\n", timestamp_in_ms(&table));
	// usleep(200 * 1000);
	// printf("TIME: %lld\n", timestamp_in_ms(&table));
	pthread_mutex_lock(&table.print_lock);
	printf("%lld %d died\n", table.dead_time, table.dead + 1);
	pthread_mutex_unlock(&table.print_lock);
	free_data(&table);

	// printf("Enter to continue...\n");
	// getchar();
	return (0);
}
