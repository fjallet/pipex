/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:40:27 by fjallet           #+#    #+#             */
/*   Updated: 2022/07/20 16:55:54 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parsing(t_vars *vars, char ** argc)
{
	int i;
	int	j;

	i = 2;
	vars->infile = argc[1];
	vars->outfile = argc[vars->argv - 1];
	vars->cmd = malloc(sizeof(char *) * vars->argv - 1);
	while (i < vars->argv - 1)
	{
		j = 0;
		vars->cmd[i - 2] = malloc(sizeof(char) * strlen(argc[i]) + 1);
		while (argc[i][j] != '\0')
		{
			vars->cmd[i - 2][j] = argc[i][j];
			j++;
		}
		vars->cmd[i - 2][j] = '\0';
		i++;
	}
	vars->cmd[i - 2] = NULL;
}

char	*ft_fullpath(t_vars *vars, char *file)
{	
	char	*temp;
	char	*path;
	
	temp = ft_strjoin(vars->paths[0], "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, file);
	free(temp);
	return (path);
}

void	ft_path(t_vars *vars, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			vars->paths = ft_split(env[i] + 5, ':');
			return ;
		}
	}
}

int	check_cmd(t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	while (vars->cmd[i])
	{
		temp = ft_fullpath(vars, vars->cmd[i]);
		if (access(temp, F_OK | X_OK) == -1)
		{
			free(temp);
			return (-1);
		}
		free(temp);
		i++;
	}
	return (0);
}

int	setup_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->pipe = malloc(sizeof(int *) * vars->numcmd);
	if (!vars->pipe)
		return (-1);
	while (i < vars->numcmd)
	{
		vars->pipe[i] = malloc(sizeof(int) * 2);
			if (!vars->pipe[i])
				return (-1);
		i++;
	}
	vars->witness = 1;
	return (0);
}
