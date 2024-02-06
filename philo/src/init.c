/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:06:50 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 11:38:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_forks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
	if (!table->forks)
	{
		print_err("table->forks", "Malloc error");
		return ;
	}
}

void	assign_forks(t_table *table)
{
	int	i;

	create_forks(table);
	i = -1;
	while (++i < table->philo_nb)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			print_err("table->forks", "mutex init has failed\n");
			return ;
		}
	}
	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].left_fork = &table->forks[i];
		if (i == table->philo_nb - 1)
			table->philos[i].right_fork = &table->forks[0];
		else
			table->philos[i].right_fork = &table->forks[i + 1];
	}
}

void	init_philo(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nb);
	if (!table->philos)
	{
		print_err("table->philos", "Malloc error");
		return ;
	}
	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].eaten = 0;
		table->philos[i].left_lock = false;
		table->philos[i].right_lock = false;
	}
}

void	init_nurse_lock(t_table *table)
{
	if (pthread_mutex_init(&table->nurse.dead_lock, NULL) != 0)
	{
		print_err("table->nurse.dead_lock", "mutex init has failed\n");
		return ;
	}
	if (pthread_mutex_init(&table->nurse.eat_lock, NULL) != 0)
	{
		print_err("table->nurse.eat_lock", "mutex init has failed\n");
		return ;
	}
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		print_err("table->print_lock", "mutex init has failed\n");
		return ;
	}
	if (pthread_mutex_init(&table->fork_lock, NULL) != 0)
	{
		print_err("table->fork_lock", "mutex init has failed\n");
		return ;
	}
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->start_time = 0;
	table->philo_nb = ft_atoll(argv[1]);
	table->die_time = ft_atoll(argv[2]);
	table->eat_time = ft_atoll(argv[3]);
	table->sleep_time = ft_atoll(argv[4]);
	table->is_end = false;
	table->dead = -1;
	if (argc == 6)
		table->eat_goal = ft_atoll(argv[5]);
	else
		table->eat_goal = -1;
	init_philo(table);
	assign_forks(table);
	init_nurse_lock(table);
	return (0);
}
