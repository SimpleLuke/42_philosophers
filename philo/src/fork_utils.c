/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:53:26 by llai              #+#    #+#             */
/*   Updated: 2024/02/07 11:56:14 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_up_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->fork_lock);
	philo->left_lock = true;
	pthread_mutex_unlock(&philo->table->fork_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	pick_up_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->fork_lock);
	philo->right_lock = true;
	pthread_mutex_unlock(&philo->table->fork_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2)
		pick_up_left_fork(philo);
	else
		pick_up_right_fork(philo);
	if (philo->id % 2)
		pick_up_right_fork(philo);
	else
		pick_up_left_fork(philo);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock);
	if (philo->id % 2)
	{
		if (philo->left_lock)
			pthread_mutex_unlock(philo->left_fork);
		if (philo->right_lock)
			pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		if (philo->right_lock)
			pthread_mutex_unlock(philo->right_fork);
		if (philo->left_lock)
			pthread_mutex_unlock(philo->left_fork);
	}
	philo->right_lock = false;
	philo->left_lock = false;
	pthread_mutex_unlock(&philo->table->fork_lock);
}
