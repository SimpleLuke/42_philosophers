/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:54:28 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 13:02:16 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	sem_wait(&philo->eat_sem);
	philo->last_eat = timestamp_in_ms(philo->table);
	philo->eaten++;
	if (philo->eaten == philo->table->eat_goal)
		sem_post(philo->table->eaten_sem);
	sem_post(&philo->eat_sem);
	if (!philo->table->is_end)
	{
		sem_wait(philo->table->print_sem);
		printf("%ld\t%d is eating\n", timestamp_in_ms(philo->table), philo->id);
		sem_post(philo->table->print_sem);
	}
	ft_usleep(philo->table->eat_time, philo->table);
}

void	sleeping(t_philo *philo)
{
	if (!philo->table->is_end)
	{
		sem_wait(philo->table->print_sem);
		printf("%ld\t%d is sleeping\n",
			timestamp_in_ms(philo->table), philo->id);
		sem_post(philo->table->print_sem);
	}
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	if (!philo->table->is_end)
	{
		sem_wait(philo->table->print_sem);
		printf("%ld\t%d is thinking\n",
			timestamp_in_ms(philo->table), philo->id);
		sem_post(philo->table->print_sem);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_eat = timestamp_in_ms(philo->table);
	if (philo->id % 2)
		ft_usleep(philo->table->eat_time, philo->table);
	while (1)
	{
		thinking(philo);
		if (philo->id % 2)
			ft_usleep(1, philo->table);
		pick_up_forks(philo);
		eating(philo);
		put_down_forks(philo);
		sleeping(philo);
	}
	return (NULL);
}
