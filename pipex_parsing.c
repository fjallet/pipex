/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:40:27 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/08 17:33:57 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_parsing(t_vars *vars, char **argc)
{
	int	i;
	int	j;

	i = 2;
	vars->infile = argc[1];
	vars->outfile = argc[vars->argv - 1];
	vars->cmd = malloc(sizeof(char *) * vars->argv - 1);
	if (!(vars->cmd))
		return (-1);
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
	return (0);
}

char	*ft_fullpath(char *path, char *file)
{	
	char	*temp;

	temp = ft_pipex_strjoin(path, "/");
	if (!temp)
		return (NULL);
	path = ft_pipex_strjoin(temp, file);
	free(temp);
	return (path);
}

int	ft_path(t_vars *vars, char **env)
{
	int	i;

	i = -1;
	while (env[i + 1] && env[++i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			vars->paths = ft_split(env[i] + 5, ':');
			return (0);
		}
	}
	return (-1);
}

/*int	check_cmd(t_vars *vars)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (vars->cmd[i])
	{
		j = 0;
		while (vars->paths[j])
		{
			temp = ft_fullpath(vars->paths[j], vars->cmd[i]);
			if (access(temp, F_OK | X_OK) == 0)
				vars->cmd[i] = ft_strlcpy(vars->cmd[i], temp);
			free(temp);
			j++;
		}
		i++;
	}
	i = 0;
	while (vars->cmd[i])
	{
		//ft_printf("%s, %i\n", vars->cmd[i], access(vars->cmd[i], F_OK | X_OK));
		if (access(vars->cmd[i], F_OK | X_OK) == -1)
			return (-1);
		i++;
	}
	return (0);
}*/

char	**check_cmd(t_vars *vars, char *cmd)
{
	int		i;
	char	*temp;
	char	**cmdf;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	cmdf = ft_split(cmd, ' ');
	i = 0;
	while (vars->paths[i])
	{
		temp = ft_fullpath(vars->paths[i], cmdf[0]);
		if (access(temp, F_OK | X_OK) == 0)
			cmdf[0] = ft_strlcpy(cmdf[0], temp);
		free(temp);
		i++;
	}
	if (access(cmdf[0], F_OK | X_OK) == -1)
	{
		perror("access");
		free_tab(cmdf);
		return (NULL);
	}
	return (cmdf);
}

int	setup_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->pipe = malloc(sizeof(int *) * (vars->numcmd));
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
