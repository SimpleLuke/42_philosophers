/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:23:46 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 21:15:40 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	check_eat_goal(t_table *table)
{
	int	i;

	i = 0;
	while (true)
	{
		sem_wait(table->eaten_sem);
		i++;
		if (i == table->philo_nb)
		{
			table->is_end = true;
			sem_post(table->dead_sem);
		}
	}
}

void	kill_and_get_childern(t_table *table)
{
	int	status;
	int	i;

	sem_wait(table->dead_sem);
	i = -1;
	while (++i < table->philo_nb)
		kill(table->pids[i], SIGKILL);
	if (table->eat_pid != -1)
		kill(table->eat_pid, SIGKILL);
	printf("All children are killed\n");
	i = -1;
	while (++i < table->philo_nb)
		waitpid(table->pids[i], &status, 0);
	if (table->eat_pid != -1)
		waitpid(table->eat_pid, &status, 0);
}
