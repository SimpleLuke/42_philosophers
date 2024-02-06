/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:10:23 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 11:01:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

long long	ft_atoll(const char *nptr)
{
	long long	num;
	int			is_neg;
	int			i;

	num = 0;
	is_neg = 1;
	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\t'
			|| nptr[i] == '\n' || nptr[i] == '\v'
			|| nptr[i] == '\r' || nptr[i] == '\f'))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		is_neg *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * is_neg);
}

void	ft_usleep(uint64_t ms, t_table *table)
{
	uint64_t	target;

	target = timestamp_in_ms(table) + ms;
	while (timestamp_in_ms(table) < target)
		usleep(100);
}

bool	check_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atoll(argv[i]) <= 0)
			return (false);
	}
	return (true);
}
