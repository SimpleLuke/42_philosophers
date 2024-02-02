/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:06:50 by llai              #+#    #+#             */
/*   Updated: 2024/02/02 18:51:37 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
	if (!table->forks)
	{
		print_err("table->forks", "Malloc error");
		return ;
	}
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

int	init_table(t_table *table, int argc, char **argv)
{
	table->start_time = 0;
	timestamp_in_ms(table);
	table->philo_nb = ft_atoll(argv[1]);
	table->die_time = ft_atoll(argv[2]);
	table->eat_time = ft_atoll(argv[3]);
	table->sleep_time = ft_atoll(argv[4]);
	if (argc == 6)
		table->eat_goal = ft_atoll(argv[5]);
	else
		table->eat_goal = -1;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nb);
	if (!table->philos)
	{
		print_err("table->philos", "Malloc error");
		return(EXIT_FAILURE);
	}
	assign_forks(table);
	return (0);
}
