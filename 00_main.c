/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <larraingonzalez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:47:13 by lagonzal          #+#    #+#             */
/*   Updated: 2023/02/07 16:44:47 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argv, char **argl, char **envp)
{
	t_cmnd_line	*args;
	int			fd[2];
	int			id;

	args = ft_arg_check(argv, argl, envp);
	if (pipe(fd) == -1)
	{
		ft_free_struct(args, 4);
		return (-1);
	}
	id = fork();
	if (id == 0)
	{
		child_procces(argv, fd, args);
	}
	else
	{
		if (args)
		ft_free_struct(args, 2);
	}	
}
