/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/02 23:39:24 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <unistd.h>

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d pick up: %d\n", philo->num, philo->okay);
	if (!philo->okay)
	{
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a left fork\n", timestamp_in_ms(philo->table), philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a right fork\n", timestamp_in_ms(philo->table), philo->num);
	}
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a right fork\n", timestamp_in_ms(philo->table), philo->num);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %d has taken a left fork\n", timestamp_in_ms(philo->table), philo->num);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d eating: %d\n", philo->num, philo->okay);
	if (!philo->okay)
	{
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	philo->last_eat = timestamp_in_ms(philo->table);
	printf("%lld %d is eating\n", timestamp_in_ms(philo->table), philo->num);
	ft_usleep(philo->table->eat_time, philo->table);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d put down: %d\n", philo->num, philo->okay);
	if (!philo->okay)
	{
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	pthread_mutex_unlock(philo->left_fork);
	// printf("%lld %d put down a left fork\n", timestamp_in_ms(philo->table), philo->num);
	pthread_mutex_unlock(philo->right_fork);
	// printf("%lld %d put down a right fork\n", timestamp_in_ms(philo->table), philo->num);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d sleeping: %d\n", philo->num, philo->okay);
	if (!philo->okay)
	{
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	printf("%lld %d is sleeping\n", timestamp_in_ms(philo->table), philo->num);
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d thinking: %d\n", philo->num, philo->okay);
	if (!philo->okay)
	{
		pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	printf("%lld %d is thinking\n", timestamp_in_ms(philo->table), philo->num);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->okay)
	{
		pick_up_forks(philo);
		eating(philo);
		put_down_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	stop_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
	{
		pthread_mutex_lock(&table->nurse.dead_lock);
		table->philos[i].okay = false;
		if (pthread_detach(table->philos[i].tid) != 0)
			print_err("Detach failed", NULL);
		pthread_mutex_unlock(&table->nurse.dead_lock);
	}
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			i;
	uint64_t	now;

	table = (t_table *)arg;
	while (true)
	{
		i = -1;
		while (++i < table->philo_nb)
		{
			now = timestamp_in_ms(table);
			if (now - table->philos[i].last_eat > table->die_time)
			{
				// printf("%d: last eat %lld now: %lld die:%lld\n", i + 1, table->philos[i].last_eat, now, table->die_time);
				stop_philos(table);
				printf("%lld %d died\n", now, i + 1);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	set_pthread(t_table *table)
{
	int	i;

	if (pthread_create(&table->nurse.tid, NULL, monitor, (void *)table) != 0)
	{
		print_err("Table->nurse", "Thread can't be created");
		return ;
	}
	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].num = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_eat = timestamp_in_ms(table);
		if (pthread_create(&table->philos[i].tid, NULL, routine, (void *)&table->philos[i]) != 0)
		{
			print_err("Table->philos", "Thread can't be created");
			return ;
		}
	}
}

void	join_pthread(t_table *table)
{
	int	i;

	pthread_join(table->nurse.tid, NULL);
	i = -1;
	while (++i < table->philo_nb)
		pthread_join(table->philos[i].tid, NULL);
}

void	set_time(t_table *table)
{
	int	i;

	table->start_time = 0;
	timestamp_in_ms(table);
	i = -1;
	while (++i < table->philo_nb)
		table->philos[i].last_eat = timestamp_in_ms(table);
}

void	start_simulation(t_table *table)
{
	// set_time(table);
	set_pthread(table);
	join_pthread(table);
}
