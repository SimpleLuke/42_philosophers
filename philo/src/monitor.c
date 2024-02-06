/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:51:27 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 11:51:37 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	stop_philos(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->nurse.dead_lock);
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_unlock(&table->print_lock);
	table->is_end = true;
	i = -1;
	while (++i < table->philo_nb)
		put_down_forks(&table->philos[i]);
	pthread_mutex_unlock(&table->nurse.dead_lock);
}

bool	check_eat_goal(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
		if (table->philos[i].eaten < table->eat_goal)
			return (false);
	return (true);
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (true)
	{
		if (table->eat_goal > -1 && check_eat_goal(table))
		{
			stop_philos(table);
			return (NULL);
		}
		i = -1;
		while (++i < table->philo_nb)
		{
			if (timestamp_in_ms(table) - table->philos[i].last_eat
				> table->die_time)
			{
				stop_philos(table);
				table->dead = i;
				table->dead_time = timestamp_in_ms(table);
				return (NULL);
			}
		}
	}
	return (NULL);
}
