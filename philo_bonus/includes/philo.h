/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:35:29 by llai              #+#    #+#             */
/*   Updated: 2024/02/11 16:31:18 by llai             ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_nurse
{
	pthread_t		tid;
}	t_nurse;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	struct s_table	*table;
	uint64_t		last_eat;
	int				eaten;
	sem_t			eat_sem;
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
	int				dead;
	uint64_t		dead_time;
	bool			is_end;
	sem_t			*philo_sem;
	sem_t			*dead_sem;
	sem_t			*dead_msg_sem;
	sem_t			*eaten_sem;
	sem_t			*print_sem;
	sem_t			*time_sem;
	int				child_idx;
	int				*pids;
	int				eat_pid;
}	t_table;

bool		check_argv(int argc, char **argv);
int			print_err(char *msg1, char *msg2, int errstate);
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
void		err_exit(int errstate, t_table *table);
void		kill_and_get_childern(t_table *table);
void		check_eat_goal(t_table *table);
void		close_sem(t_table *table);
void		check_sem(void);

#endif // !PHILO_H
