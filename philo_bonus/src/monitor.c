/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:51:27 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 13:28:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	stop_philos(t_table *table)
{
	table->is_end = true;
	sem_post(table->dead_sem);
}

void	*monitor(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	ft_usleep(100, table);
	while (true)
	{
		sem_wait(&table->philos[table->child_idx].eat_sem);
		if (timestamp_in_ms(table) - table->philos[table->child_idx].last_eat
			> table->die_time)
		{
			stop_philos(table);
			table->dead = table->child_idx + 1;
			table->dead_time = timestamp_in_ms(table);
			sem_wait(table->dead_msg_sem);
			sem_wait(table->print_sem);
			printf("%ld\t%d died\n", table->dead_time, table->dead);
			return (NULL);
		}
		sem_post(&table->philos[table->child_idx].eat_sem);
	}
	return (NULL);
}
