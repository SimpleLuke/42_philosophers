/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:54:28 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 11:56:45 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.eat_lock);
	philo->last_eat = timestamp_in_ms(philo->table);
	philo->eaten++;
	pthread_mutex_unlock(&philo->table->nurse.eat_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%ld\t%d is eating\n", timestamp_in_ms(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->eat_time, philo->table);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%ld\t%d is sleeping\n",
			timestamp_in_ms(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%ld\t%d is thinking\n",
			timestamp_in_ms(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(1, philo->table);
	while (1)
	{
		pthread_mutex_lock(&philo->table->nurse.dead_lock);
		if (philo->table->is_end)
		{
			pthread_mutex_unlock(&philo->table->nurse.dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		pick_up_forks(philo);
		eating(philo);
		put_down_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
