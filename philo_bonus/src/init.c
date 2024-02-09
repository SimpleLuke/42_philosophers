/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:06:50 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 12:34:08 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nb);
	if (!table->philos)
	{
		print_err("table->philos", "Malloc error", EXIT_FAILURE);
		return ;
	}
	table->pids = (int *)malloc(sizeof(int) * table->philo_nb);
	if (!table->pids)
	{
		print_err("table->pids", "Malloc error", EXIT_FAILURE);
		return ;
	}
	i = -1;
	while (++i < table->philo_nb)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].eaten = 0;
	}
}

void	init_sem(t_table *table)
{
	table->philo_sem = sem_open("/philo_sem", O_CREAT | O_EXCL,
			0666, table->philo_nb);
	if (table->philo_sem == SEM_FAILED)
		err_exit(print_err("table->philo_sem", "SEM philo error",
				EXIT_FAILURE), table);
	table->dead_sem = sem_open("/dead_sem", O_CREAT | O_EXCL, 0666, 0);
	if (table->dead_sem == SEM_FAILED)
		err_exit(print_err("table->dead_sem", "SEM dead error",
				EXIT_FAILURE), table);
	table->dead_msg_sem = sem_open("/dead_msg_sem", O_CREAT | O_EXCL, 0666, 1);
	if (table->dead_msg_sem == SEM_FAILED)
		err_exit(print_err("table->dead_msg_sem", "SEM dead msg error",
				EXIT_FAILURE), table);
	table->eaten_sem = sem_open("/eaten_sem", O_CREAT | O_EXCL, 0666, 0);
	if (table->eaten_sem == SEM_FAILED)
		err_exit(print_err("table->eaten_sem", "SEM eat error",
				EXIT_FAILURE), table);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->start_time = 0;
	table->child_idx = 0;
	table->philo_nb = ft_atoll(argv[1]);
	table->die_time = ft_atoll(argv[2]);
	table->eat_time = ft_atoll(argv[3]);
	table->sleep_time = ft_atoll(argv[4]);
	table->is_end = false;
	table->dead = -1;
	table->eat_pid = -1;
	if (argc == 6)
		table->eat_goal = ft_atoll(argv[5]);
	else
		table->eat_goal = -1;
	init_philo(table);
	init_sem(table);
	return (0);
}
