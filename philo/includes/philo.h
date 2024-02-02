/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:35:29 by llai              #+#    #+#             */
/*   Updated: 2024/02/02 23:04:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_nurse {
	pthread_t		tid;
	pthread_mutex_t dead_lock;
}	t_nurse;

typedef struct s_philo
{
	int				num;
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	uint64_t		last_eat;
	bool			okay;
}	t_philo;

typedef struct s_table
{
	int				philo_nb;
	t_philo			*philos;
	t_nurse			nurse;
	uint64_t		start_time;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				eat_goal;
	pthread_mutex_t	*forks;
}	t_table;

void		print_err(char *msg1, char *msg2);
long long	ft_atoll(const char *nptr);
uint64_t	timestamp_in_ms(t_table *table);
int			init_table(t_table *table, int argc, char **argv);
void		start_simulation(t_table *table);
void		free_data(t_table *table);
void		ft_usleep(uint64_t ms, t_table *table);

#endif // !PHILO_H
