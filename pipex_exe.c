/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:49:44 by fjallet           #+#    #+#             */
/*   Updated: 2022/07/20 16:32:16 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(t_vars *vars, char **env)
{
	vars->fd = open(vars->infile, O_RDONLY);
	if (vars->fd == -1)
		return (-1);
	pipe(vars->pipe[0]);
	vars->pid = fork();
	if (vars->pid == -1)
		return (-1);
	else if (vars->pid == 0)
	{
		if (dup2(vars->fd, 0) == -1 || dup2(vars->pipe[0][1], 1) == -1)
			return (-1);
		close(vars->fd);
		close(vars->pipe[0][1]);
		close(vars->pipe[0][0]);
		execve(vars->cmd[0], &vars->cmd[0], env);
	}
	else if (vars->pid != 0 && vars->pid != -1)
	{
		close(vars->fd);
		close(vars->pipe[0][1]);
	}
	return (0);
}

int	mid_cmd(t_vars *vars, char **env, int i)
{
	if (pipe(vars->pipe[i]) == -1)
		return (-1);
	vars->pid = fork();
	if (vars->pid == -1)
		return (-1);
	else if (vars->pid == 0)
	{
		if (dup2(vars->pipe[i - 1][0], 0) == -1 || dup2(vars->pipe[i][1], 1) == -1)
			return (-1);
		close(vars->pipe[i - 1][0]);
		close(vars->pipe[i][1]);
		close(vars->pipe[i][0]);
		execve(vars->cmd[i], &vars->cmd[i], env);
	}
	else if (vars->pid != 0 && vars->pid != -1)
	{
		close(vars->pipe[i - 1][0]);
		close(vars->pipe[i][1]);
	}
	return (0);
}

int	last_cmd(t_vars *vars, int i)
{
	int 	fd;
	int		num;
	char	buf[1000];

	fd = open(vars->outfile, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
		return (-1);
	num = 1;
	while (num > 0)
	{
		num = read(vars->pipe[i][0], buf, 1000);
		write(fd, buf, strlen(buf));
	}
	close(vars->pipe[i][0]);
	close(fd);
	return (0);
}