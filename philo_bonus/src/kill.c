/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:23:46 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 19:18:59 by llai             ###   ########.fr       */
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
		// printf("WAIT\n");
		sem_wait(table->eaten_sem);
		i++;
		// printf("ADD 1 to i: %d, phi nb = %d\n", i, table->philo_nb);
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

	// printf("I am the parent here\n");
	// ft_usleep(10, table);
	// printf("CHILD: %d\n", table->pids[0]);
	sem_wait(table->dead_sem);
	i = -1;
	while (++i < table->philo_nb)
		kill(table->pids[i], SIGKILL);
	if (table->eat_pid != -1)
		kill(table->eat_pid, SIGKILL);
	printf("All children are killed\n");
	i = -1;
	while (++i < table->philo_nb)
	{
		waitpid(table->pids[i], &status, 0);
		if (WIFEXITED(status))
			printf("In Parent: Child [%d] terminated normally.\n", table->pids[i]);
		else if (WIFSIGNALED(status))
		{
			printf("In Parent: Child [%d] was interrupted\n", table->pids[i]);
			if (WTERMSIG(status) == SIGTERM)
				printf("In Parent: Child [%d] got the %d signal, SIGTERM\n", table->pids[i], WTERMSIG(status));
			if (WTERMSIG(status) == SIGKILL)
				printf("In Parent: Child [%d] got the %d signal, SIGKILL\n", table->pids[i], WTERMSIG(status));
		}
	}
	if (table->eat_pid != -1)
	{
		waitpid(table->eat_pid, &status, 0);
		if (WIFEXITED(status))
			printf("In Parent: Child [%d] terminated normally.\n", table->eat_pid);
		else if (WIFSIGNALED(status))
		{
			printf("In Parent: Child [%d] was interrupted\n", table->eat_pid);
			if (WTERMSIG(status) == SIGTERM)
				printf("In Parent: Child [%d] got the %d signal, SIGTERM\n", table->eat_pid, WTERMSIG(status));
			if (WTERMSIG(status) == SIGKILL)
				printf("In Parent: Child [%d] got the %d signal, SIGKILL\n", table->eat_pid, WTERMSIG(status));
		}
	}
}
