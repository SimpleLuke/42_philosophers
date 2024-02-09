/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:35:28 by llai              #+#    #+#             */
/*   Updated: 2024/02/09 12:34:17 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static uint64_t	gettimeofday_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + tv.tv_usec / 1000);
}

uint64_t	timestamp_in_ms(t_table *table)
{
	if (table->start_time == 0)
		table->start_time = gettimeofday_ms();
	return (gettimeofday_ms() - table->start_time);
}

void	set_time(t_table *table)
{
	timestamp_in_ms(table);
}
