/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:36 by llai              #+#    #+#             */
/*   Updated: 2024/02/11 16:10:11 by llai             ###   ########.fr       */
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
	if (!check_argv(argc, argv))
	{
		print_err("Invalid arguments",
			"Number must be valid and greater than zero");
		return (EXIT_FAILURE);
	}
	init_table(&table, argc, argv);
	start_simulation(&table);
	pthread_mutex_lock(&table.print_lock);
	if (table.dead != -1)
		printf("%ld\t%d died\n", table.dead_time, table.dead + 1);
	pthread_mutex_unlock(&table.print_lock);
	free_data(&table);
	return (0);
}
