/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 18:44:27 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//
// void	set_pthread(t_table *table)
// {
// 	int	i;
//
// 	if (pthread_create(&table->nurse.tid, NULL, monitor, (void *)table) != 0)
// 	{
// 		print_err("Table->nurse", "Thread can't be created");
// 		return ;
// 	}
// 	i = -1;
// 	while (++i < table->philo_nb)
// 	{
// 		table->philos[i].id = i + 1;
// 		table->philos[i].table = table;
// 		table->philos[i].last_eat = timestamp_in_ms(table);
// 		if (pthread_create(&table->philos[i].tid, NULL, routine,
// 				(void *)&table->philos[i]) != 0)
// 		{
// 			print_err("Table->philos", "Thread can't be created");
// 			return ;
// 		}
// 	}
// }

// void	join_pthread(t_table *table)
// {
// 	int	i;
//
// 	pthread_join(table->nurse.tid, NULL);
// 	i = -1;
// 	while (++i < table->philo_nb)
// 		pthread_join(table->philos[i].tid, NULL);
// }
//
void	run_child(t_table *table, int child_idx)
{
	sem_init(&table->philos[table->child_idx].eat_sem, 0, 1);
	if (pthread_create(&table->philos[child_idx].tid, NULL, routine, (void *)&table->philos[child_idx]) != 0)
		err_exit(print_err("Table->nurse", "Thread can't be created", EXIT_FAILURE), table);
	if (pthread_create(&table->nurse.tid, NULL, monitor, (void *)table) != 0)
		err_exit(print_err("Table->nurse", "Thread can't be created", EXIT_FAILURE), table);
	pthread_join(table->philos[child_idx].tid, NULL);
	pthread_join(table->nurse.tid, NULL);
	// routine(&table->philos[child_idx]);
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

	// set_pthread(table);
	// join_pthread(table);
}
