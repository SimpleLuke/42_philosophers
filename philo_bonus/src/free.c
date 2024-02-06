/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:59:59 by llai              #+#    #+#             */
/*   Updated: 2024/02/06 18:34:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_data(t_table *table)
{
	ft_free((void **)&table->philos);
	ft_free((void **)&table->pids);
}
