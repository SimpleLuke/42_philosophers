/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:53:26 by llai              #+#    #+#             */
/*   Updated: 2024/02/08 16:39:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	pick_up_left_fork(t_philo *philo)
{
	sem_wait(philo->table->philo_sem);
	// philo->left_lock = true;
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
}

void	pick_up_right_fork(t_philo *philo)
{
	sem_wait(philo->table->philo_sem);
	// philo->right_lock = true;
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
}

void	pick_up_forks(t_philo *philo)
{
	// pick_up_left_fork(philo);
	// pick_up_left_fork(philo);
	sem_wait(philo->table->philo_sem);
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	sem_wait(philo->table->philo_sem);
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	// if (philo->id % 2)
	// 	pick_up_left_fork(philo);
	// else
	// 	pick_up_right_fork(philo);
	// if (philo->id % 2)
	// 	pick_up_right_fork(philo);
	// else
	// 	pick_up_left_fork(philo);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->table->philo_sem);
	sem_post(philo->table->philo_sem);
	// if (philo->id % 2)
	// {
	// 	if (philo->left_lock)
	// 	{
	// 		sem_post(philo->table->philo_sem);
	// 		philo->left_lock = false;
	// 	}
	// 	if (philo->right_lock)
	// 	{
	// 		sem_post(philo->table->philo_sem);
	// 		philo->right_lock = false;
	// 	}
	// }
	// else
	// {
	// 	if (philo->right_lock)
	// 	{
	// 		sem_post(philo->table->philo_sem);
	// 		philo->right_lock = false;
	// 	}
	// 	if (philo->left_lock)
	// 	{
	// 		sem_post(philo->table->philo_sem);
	// 		philo->left_lock = false;
	// 	}
	// }
}
