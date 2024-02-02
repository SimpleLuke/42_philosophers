/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/02 19:46:29 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <unistd.h>

void	*trythis(void *arg)
{
	// t_table *table;
	t_philo		*philo;

	// table = (t_table *)arg;
	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	printf("%d: Starting...\n", philo->num);
	usleep(3000 * 1000);
	printf("%d: Finished...\n", philo->num);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	set_pthread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].num = i;
		if (pthread_create(&table->philos[i].tid, NULL, trythis, (void *)&table->philos[i]) != 0)
		{
			print_err("Table->philos", "Thread can't be created");
			return ;
		}
	}
}

void	join_pthread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->philos[i].tid, NULL);
}

void	start_simulation(t_table *table)
{
	set_pthread(table);
	join_pthread(table);
}
