/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:53:26 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 13:19:21 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

void	pick_up_forks(t_philo *philo)
{
	sem_wait(philo->table->philo_sem);
	sem_wait(philo->table->print_sem);
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	sem_post(philo->table->print_sem);
	sem_wait(philo->table->philo_sem);
	sem_wait(philo->table->print_sem);
	if (!philo->table->is_end)
		printf("%ld\t%d has taken a fork\n",
			timestamp_in_ms(philo->table), philo->id);
	sem_post(philo->table->print_sem);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->table->philo_sem);
	sem_post(philo->table->philo_sem);
}
