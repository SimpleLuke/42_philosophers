/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:36 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 21:09:55 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_table	table;

	sem_unlink("/dead_sem");
	sem_unlink("/dead_msg_sem");
	sem_unlink("/eaten_sem");
	// sem_unlink("/msg_sem");
	sem_unlink("/philo_sem");
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
	init_table(&table, argc, argv);
	start_simulation(&table);
	kill_and_get_childern(&table);
	// pthread_mutex_lock(&table.print_lock);
	sem_close(table.philo_sem);
	sem_close(table.dead_sem);
	sem_close(table.dead_msg_sem);
	sem_close(table.eaten_sem);
	// sem_close(table.eat_sem);
	sem_unlink("/dead_sem");
	// sem_unlink("/msg_sem");
	sem_unlink("/dead_msg_sem");
	sem_unlink("/philo_sem");
	sem_unlink("/eaten_sem");
	// pthread_mutex_unlock(&table.print_lock);
	free_data(&table);
	return (0);
}
