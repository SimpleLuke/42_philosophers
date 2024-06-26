/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:35:29 by llai              #+#    #+#             */
/*   Updated: 2024/02/11 13:20:12 by llai             ###   ########.fr       */
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

typedef struct s_nurse
{
	pthread_t		tid;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
}	t_nurse;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			left_lock;
	bool			right_lock;
	struct s_table	*table;
	uint64_t		last_eat;
	int				eaten;
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
	int				dead;
	uint64_t		dead_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	loop_lock;
	bool			is_end;
}	t_table;

bool		check_argv(int argc, char **argv);
void		print_err(char *msg1, char *msg2);
long long	ft_atoll(const char *nptr);
uint64_t	timestamp_in_ms(t_table *table);
int			init_table(t_table *table, int argc, char **argv);
void		start_simulation(t_table *table);
void		*routine(void *arg);
void		*monitor(void *arg);
void		pick_up_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		free_data(t_table *table);
void		ft_usleep(uint64_t ms, t_table *table);
void		set_time(t_table *table);

#endif // !PHILO_H
