/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:54:28 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 12:36:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	eating(t_philo *philo)
{
	sem_wait(philo->table->eat_sem);
	philo->last_eat = timestamp_in_ms(philo->table);
	philo->eaten++;
	sem_post(philo->table->eat_sem);
	if (!philo->table->is_end)
		printf("%ld\t%d is eating\n", timestamp_in_ms(philo->table), philo->id);
	ft_usleep(philo->table->eat_time, philo->table);
}

void	sleeping(t_philo *philo)
{
	if (!philo->table->is_end)
		printf("%ld\t%d is sleeping\n",
			timestamp_in_ms(philo->table), philo->id);
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	if (!philo->table->is_end)
		printf("%ld\t%d is thinking\n",
			timestamp_in_ms(philo->table), philo->id);
}

void	*routine(void *arg)
// void	*routine(t_philo *philo)
{
	t_philo		*philo;
	//
	philo = (t_philo *)arg;
	// if (philo->id % 2)
	// 	ft_usleep(1, philo->table);
	// sem_wait(philo->table->dead_sem);
	while (1)
	{
	// printf("HEY\n");
		thinking(philo);
		pick_up_forks(philo);
		eating(philo);
		put_down_forks(philo);
		sleeping(philo);
	}
	return (NULL);
}
