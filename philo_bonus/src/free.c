/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:59:59 by llai              #+#    #+#             */
/*   Updated: 2024/02/11 16:32:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	check_sem(void)
{
	sem_unlink("/dead_sem");
	sem_unlink("/dead_msg_sem");
	sem_unlink("/philo_sem");
	sem_unlink("/eaten_sem");
	sem_unlink("/print_sem");
	sem_unlink("/time_sem");
}

void	close_sem(t_table *table)
{
	sem_close(table->philo_sem);
	sem_close(table->dead_sem);
	sem_close(table->dead_msg_sem);
	sem_close(table->eaten_sem);
	sem_close(table->print_sem);
	sem_close(table->time_sem);
	sem_unlink("/dead_sem");
	sem_unlink("/dead_msg_sem");
	sem_unlink("/philo_sem");
	sem_unlink("/eaten_sem");
	sem_unlink("/print_sem");
	sem_unlink("/time_sem");
}

void	free_data(t_table *table)
{
	ft_free((void **)&table->philos);
	ft_free((void **)&table->pids);
}
