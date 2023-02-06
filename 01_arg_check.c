/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <larraingonzalez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:48:06 by lagonzal          #+#    #+#             */
/*   Updated: 2023/02/06 20:51:01 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



t_cmnd_line	*ft_open_fds(int argv, char **argl);
char		***ft_get_cmnds(int argv, char **argl);
char		**ft_get_path(char **envp);
t_cmnd_line	*ft_check_access(char **paths, t_cmnd_line *args);


t_cmnd_line	*ft_arg_check(int argv, char **argl, char **envp)
{
	t_cmnd_line	*args;

	if (argv != 5)
	{	
		ft_putstr_fd("Error.\n", 2);
		ft_putstr_fd("Number of variables different from 5.\n", 1);
		return(NULL);
	}
	args = ft_open_fds(argv, argl);
	if (!args)
		return (NULL);
	args->path = ft_get_path(envp);
	if (!(args->path))
		return (ft_free_struct(args, 1));
	args->cmnds = ft_get_cmnds(argv, argl);
	if (!(args->cmnds))
		return (ft_free_struct(args, 2));
	args = ft_check_access(args->path, args);
	if (!args)
		return (ft_free_struct(args, 2));
	return (args);
}

t_cmnd_line	*ft_open_fds(int argv, char **argl)
{
	t_cmnd_line	*args;

	args = malloc(sizeof(t_cmnd_line));
	args->fd_in = open(argl[0], O_RDONLY);
	if (args->fd_in < 0)
		return (free(args), NULL);
	args->fd_out = open(argl[argv - 1], O_WRONLY);
	if (args->fd_out < 0)
	{
		close(args->fd_in);
		return (free(args), NULL);
	}
	return (args);
}

char	***ft_get_cmnds(int argv, char **argl)
{
	char	***cmnds;
	int		i;
	int		j;

	cmnds = malloc((argv - 2) * sizeof(char **));
	if (!cmnds)
		return (NULL);
	cmnds[argv - 3] = NULL;
	i = 0;
	j = 1;
	while (i < argv - 3)
	{
		cmnds[i] = ft_split(argl[j], ' ');
		if (!cmnds[i])
			return (NULL);
		i++;
		j++;
	}
	return (cmnds);
}

char	**ft_get_path(char **envp)
{
	char	**path;
	char	*env_path;
	char	*bar_add;
	int		i;

	i = 0;
	env_path = (ft_strnstr(envp[0], "PATH", 4));
	while(!env_path && envp[i])
		env_path = (ft_strnstr(envp[++i], "PATH", 4));
	if (!env_path)
		return (NULL);
	path = ft_split(&env_path[5], ':');
	i = -1;
	while (path[++i])
	{
		bar_add = ft_strjoin(path[i], "/");
		if (bar_add == NULL)
			return(NULL);
		free(path[i]);
		path[i] = bar_add;
	}
	return (path);
}

t_cmnd_line	*ft_check_access(char **paths, t_cmnd_line *args)
{
	char	*full_path;
	char	***aux_c;
	int		i;
	int		err;
	int		j;

	aux_c = args->cmnds;
	i = -1;
	while(aux_c[++i])
	{
		j = -1;
		while (paths[++j])
		{
			full_path = ft_strjoin(paths[j], aux_c[i][0]);
			err = access(full_path, F_OK);
			if (err == 0)
			{
				free(aux_c[i][0]);
				aux_c[i][0] = full_path;
				break;
			}
				free(full_path);
		}
	}
	return (args);
}