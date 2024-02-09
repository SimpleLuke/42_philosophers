/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 12:33:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	run_child(t_table *table, int child_idx)
{
	sem_init(&table->philos[table->child_idx].eat_sem, 0, 1);
	if (pthread_create(&table->philos[child_idx].tid, NULL, routine,
			(void *)&table->philos[child_idx]) != 0)
		err_exit(print_err("Table->nurse", "Thread can't be created",
				EXIT_FAILURE), table);
	if (pthread_create(&table->nurse.tid, NULL, monitor, (void *)table) != 0)
		err_exit(print_err("Table->nurse", "Thread can't be created",
				EXIT_FAILURE), table);
	pthread_join(table->philos[child_idx].tid, NULL);
	pthread_join(table->nurse.tid, NULL);
}

void	start_simulation(t_table *table)
{
	set_time(table);
	while (table->child_idx < table->philo_nb)
	{
		table->pids[table->child_idx] = fork();
		if (table->pids[table->child_idx] == -1)
			err_exit(EXIT_FAILURE, table);
		if (table->pids[table->child_idx] == 0)
			run_child(table, table->child_idx);
		table->child_idx++;
	}
	if (table->eat_goal > 0)
	{
		table->eat_pid = fork();
		if (table->eat_pid == -1)
			err_exit(EXIT_FAILURE, table);
		if (table->eat_pid == 0)
			check_eat_goal(table);
	}
}
