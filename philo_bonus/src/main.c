/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:36 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 21:20:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5)
	{
		print_err("Invalid arguments",
			"./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (!check_argv(argc, argv))
	{
		print_err("Invalid arguments",
			"Number must be valid and greater than zero", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	check_sem();
	init_table(&table, argc, argv);
	start_simulation(&table);
	kill_and_get_childern(&table);
	close_sem(&table);
	free_data(&table);
	return (0);
}
