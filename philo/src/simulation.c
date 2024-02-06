/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 11:55:06 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

void	set_pthread(t_table *table)
{
	int	i;

	if (pthread_create(&table->nurse.tid, NULL, monitor, (void *)table) != 0)
	{
		print_err("Table->nurse", "Thread can't be created");
		return ;
	}
	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_eat = timestamp_in_ms(table);
		if (pthread_create(&table->philos[i].tid, NULL, routine,
				(void *)&table->philos[i]) != 0)
		{
			print_err("Table->philos", "Thread can't be created");
			return ;
		}
	}
}

void	join_pthread(t_table *table)
{
	int	i;

	pthread_join(table->nurse.tid, NULL);
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->philos[i].tid, NULL);
}

void	start_simulation(t_table *table)
{
	set_time(table);
	set_pthread(table);
	join_pthread(table);
}
