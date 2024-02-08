/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:51:27 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 18:33:24 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void	stop_philos(t_table *table)
{
	table->is_end = true;
	sem_post(table->dead_sem);
}

// bool	check_eat_goal(t_table *table)
// {
// 	if (table->philos[table->child_idx].eaten < table->eat_goal)
// 		return (false);
// 	return (true);
// }

void	*monitor(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	ft_usleep(100, table);
	while (true)
	{
		// ft_usleep(1, table);
		// printf("%d: now:%ld last eat: %ld die time: %ld\n", table->child_idx + 1, timestamp_in_ms(table), table->philos[table->child_idx].last_eat, table->die_time);
		// sem_wait(table->eaten_sem);
		// if (table->eat_goal > -1)
		// {
		// 	stop_philos(table);
		// 	// sem_close(table->eat_sem);
		// 	return (NULL);
		// }
		// ft_usleep(10, table);
		sem_wait(&table->philos[table->child_idx].eat_sem);
		// printf("%d: now:%ld last eat: %ld die time: %ld\n", table->child_idx + 1, timestamp_in_ms(table), table->philos[table->child_idx].last_eat, table->die_time);
		if (timestamp_in_ms(table) - table->philos[table->child_idx].last_eat
			> table->die_time)
		{
		// printf("%d: now:%ld last eat: %ld die time: %ld\n", table->child_idx + 1, timestamp_in_ms(table), table->philos[table->child_idx].last_eat, table->die_time);
			stop_philos(table);
			table->dead = table->child_idx + 1;
			table->dead_time = timestamp_in_ms(table);
			sem_wait(table->dead_msg_sem);
			printf("%ld\t%d died\n", table->dead_time, table->dead);
			// sem_close(table->eat_sem);
			return (NULL);
		}
		sem_post(&table->philos[table->child_idx].eat_sem);
	}
	return (NULL);
}
