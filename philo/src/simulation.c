/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:30:09 by llai              #+#    #+#             */
/*   Updated: 2024/02/03 20:44:56 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

void	pick_up_forks(t_philo *philo)
{
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// if (!philo->table->is_end)
	// {
	// 	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_lock = true;
		// set_time(philo->table);
		pthread_mutex_lock(&philo->table->print_lock);
		if (!philo->table->is_end)
			printf("%lld %d has taken a left fork\n", timestamp_in_ms(philo->table), philo->num);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_lock = true;
		// set_time(philo->table);
		pthread_mutex_lock(&philo->table->print_lock);
		if (!philo->table->is_end)
			printf("%lld %d has taken a right fork\n", timestamp_in_ms(philo->table), philo->num);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// if (!philo->okay)
	// {
	// 	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_lock = true;
		// set_time(philo->table);
		pthread_mutex_lock(&philo->table->print_lock);
		if (!philo->table->is_end)
			printf("%lld %d has taken a right fork\n", timestamp_in_ms(philo->table), philo->num);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_lock = true;
		// set_time(philo->table);
		pthread_mutex_lock(&philo->table->print_lock);
		if (!philo->table->is_end)
			printf("%lld %d has taken a left fork\n", timestamp_in_ms(philo->table), philo->num);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}

void	eating(t_philo *philo)
{
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// // printf("%d eating: %d\n", philo->num, philo->okay);
	// if (!philo->okay)
	// {
	// 	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	pthread_mutex_lock(&philo->table->nurse.eat_lock);
	philo->last_eat = timestamp_in_ms(philo->table);
	philo->eaten++;
	// printf("%d : last eat %lld\n", philo->num, philo->last_eat);
	pthread_mutex_unlock(&philo->table->nurse.eat_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%lld %d is eating\n", timestamp_in_ms(philo->table), philo->num);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->eat_time, philo->table);
}

void	put_down_forks(t_philo *philo)
{
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// printf("%d put down: %d\n", philo->num, philo->okay);
	// if (!philo->okay)
	// {
		// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
		// return ;
	// }
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	if (philo->num % 2)
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
	// printf("%lld %d put down a left fork\n", timestamp_in_ms(philo->table), philo->num);
	// printf("%lld %d put down a right fork\n", timestamp_in_ms(philo->table), philo->num);
}

void	sleeping(t_philo *philo)
{
	// printf("%lld %d A\n", timestamp_in_ms(philo->table), philo->num);
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// // printf("%d sleeping: %d\n", philo->num, philo->okay);
	// if (!philo->table->is_end)
	// {
	// 	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// 	return ;
	// }
	// // printf("%lld %d B\n", timestamp_in_ms(philo->table), philo->num);
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// printf("%lld %d C\n", timestamp_in_ms(philo->table), philo->num);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%lld %d is sleeping\n", timestamp_in_ms(philo->table), philo->num);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	// pthread_mutex_lock(&philo->table->nurse.dead_lock);
	// // printf("%d thinking: %d\n", philo->num, philo->okay);
	// if (!philo->okay)
	// {
	// 	pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->table->nurse.dead_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->is_end)
		printf("%lld %d is thinking\n", timestamp_in_ms(philo->table), philo->num);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	// philo->last_eat = timestamp_in_ms(philo->table);
	// printf("RUNNING: %d...\n", philo->num);
	if (philo->num % 2)
		ft_usleep(1, philo->table);
	while (1)
	{
		pthread_mutex_lock(&philo->table->nurse.dead_lock);
		if (philo->table->is_end)
		{
			// printf("%d: yes\n", philo->num);
			pthread_mutex_unlock(&philo->table->nurse.dead_lock);
			// printf("BREAKS: %d at %lld\n", philo->num, timestamp_in_ms(philo->table));
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

void	stop_philos(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->print_lock);
	printf("%lld start stopping...........\n", timestamp_in_ms(table));
	pthread_mutex_unlock(&table->print_lock);
	// i = -1;
	// // pthread_mutex_lock(&table->nurse.dead_lock);
	// while (++i < table->philo_nb)
	// {
	// 	table->philos[i].okay = false;
	// 	// if (pthread_detach(table->philos[i].tid) != 0)
	// 	// 	print_err("Detach failed", NULL);
	// }
	table->is_end = true;
	i = -1;
	while (++i < table->philo_nb)
	{
		put_down_forks(&table->philos[i]);
	}
	// pthread_mutex_unlock(&table->nurse.dead_lock);
	// printf("DONE\n");
}

// bool	check_down(t_table *table)
// {
// 	int	i;
//
// 	i = -1;
// 	while (++i < table->philo_nb)
// 	{
// 		pthread_mutex_lock(&table->nurse.dead_lock);
// 		if (table->philos[i].okay)
// 		{
// 			pthread_mutex_unlock(&table->nurse.dead_lock);
// 			return (false);
// 		}
// 		pthread_mutex_unlock(&table->nurse.dead_lock);
// 	}
// 	return (true);
//
// }
//
bool	check_eat_goal(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nb)
	{
		if (table->philos[i].eaten < table->eat_goal)
			return (false);
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			i;
	// uint64_t	now;

	table = (t_table *)arg;
	while (true)
	{
		ft_usleep(2, table);
		if (table->eat_goal > -1 && check_eat_goal(table))
		{
				pthread_mutex_lock(&table->nurse.dead_lock);
				stop_philos(table);
				pthread_mutex_unlock(&table->nurse.dead_lock);
				return (NULL);
		}
		i = -1;
		while (++i < table->philo_nb)
		{
			// now = timestamp_in_ms(table);
			// pthread_mutex_lock(&table->nurse.eat_lock);
			if (timestamp_in_ms(table) - table->philos[i].last_eat > table->die_time)
			{
				// printf("%d: last eat %lld now: %lld die:%lld\n", i + 1, table->philos[i].last_eat, now, table->die_time);
				pthread_mutex_lock(&table->nurse.dead_lock);
				stop_philos(table);
				pthread_mutex_unlock(&table->nurse.dead_lock);
				table->dead = i;
				table->dead_time = timestamp_in_ms(table);
				// pthread_mutex_unlock(&table->nurse.eat_lock);
				return (NULL);
				// while (true)
				// {
				// 	if (check_down(table))
				// 	{
				// 		table->dead = i;
				// 		table->dead_time = timestamp_in_ms(table);
				// 		// pthread_mutex_lock(&table->print_lock);
				// 		// printf("%lld %d died\n", timestamp_in_ms(table), i + 1);
				// 		// pthread_mutex_unlock(&table->print_lock);
				// 		return (NULL);
				// 	}
				// }
			}
			// pthread_mutex_unlock(&table->nurse.eat_lock);
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

void	start_simulation(t_table *table)
{
	set_time(table);
	set_pthread(table);
	join_pthread(table);
}
