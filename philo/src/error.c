/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:43:36 by llai              #+#    #+#             */
/*   Updated: 2024/02/02 17:42:14 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	print_err(char *msg1, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
	{
		write(2, " : ", 3);
		write(2, msg2, ft_strlen(msg2));
	}
	write(2, "\n", 1);
}
