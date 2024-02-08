/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:51:27 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 12:43:16 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <semaphore.h>

void	stop_philos(t_table *table)
{
	table->is_end = true;
	sem_post(table->dead_sem);
}

bool	check_eat_goal(t_table *table)
{
	if (table->philos[table->child_idx].eaten < table->eat_goal)
		return (false);
	return (true);
}

void	*monitor(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	ft_usleep(100, table);
	while (true)
	{
		sem_wait(table->eat_sem);
		// printf("%d: now:%ld last eat: %ld die time: %ld\n", table->child_idx + 1, timestamp_in_ms(table), table->philos[table->child_idx].last_eat, table->die_time);
		if (table->eat_goal > -1 && check_eat_goal(table))
		{
			stop_philos(table);
			return (NULL);
		}
		if (timestamp_in_ms(table) - table->philos[table->child_idx].last_eat
			> table->die_time)
		{
			stop_philos(table);
			table->dead = table->child_idx + 1;
			table->dead_time = timestamp_in_ms(table);
			printf("%ld\t%d died\n", table->dead_time, table->dead);
			return (NULL);
		}
		sem_post(table->eat_sem);
	}
	return (NULL);
}
