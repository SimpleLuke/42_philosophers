/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:59:59 by llai              #+#    #+#             */
/*   Updated: 2024/02/11 13:52:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_data(t_table *table)
{
	int	i;

	ft_free((void **)&table->philos);
	i = -1;
	while (++i < table->philo_nb)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->fork_lock);
	pthread_mutex_destroy(&table->nurse.dead_lock);
	pthread_mutex_destroy(&table->nurse.eat_lock);
	ft_free((void **)&table->forks);
}
