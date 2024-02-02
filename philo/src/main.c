/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:10 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:41:26 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
	{
		if (argc > 1 && !ft_strncmp("here_doc", argv[1], 9))
			err_exit(print_err("Invalid arguments",
					"./pipex here_doc LIMITER cmd cmd1 file",
					EXIT_FAILURE), NULL);
		else
			err_exit(print_err("Invalid arguments",
					"./pipex infile cmd ... cmdn outfile", EXIT_FAILURE), NULL);
	}
	else if (argc < 6 && !ft_strncmp("here_doc", argv[1], 9))
		err_exit(print_err("Invalid arguments",
				"./pipex here_doc LIMITER cmd cmd1 file", EXIT_FAILURE), NULL);
	if (!env)
		err_exit(print_err("Invalid environment variables", NULL,
				EXIT_FAILURE), NULL);
	init_data(argc, argv, env, &data);
	pipex(&data);
	printf("Enter to continue...\n");
	getchar();
	return (data.exit_code);
}
