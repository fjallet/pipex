/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:49:44 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/15 20:39:23 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(t_vars *vars, char **env)
{	
	char	**cmd;

	if (pipe(vars->pipe[0]) == -1)
		return (-1);
	if (vars->fd == -1)
		return (0);
	cmd = check_cmd(vars, vars->cmd[0]);
	if (cmd && access(cmd[0], F_OK | X_OK) != -1)
		vars->pid[0] = fork();
	if (vars->pid[0] == -1)
		return (-1);
	else if (vars->pid[0] == 0)
	{
		if (dup2(vars->fd, 0) == -1 || dup2(vars->pipe[0][1], 1) == -1)
			return (-1);
		close(vars->fd);
		close(vars->pipe[0][1]);
		close(vars->pipe[0][0]);
		if (execve(cmd[0], &cmd[0], env) == -1)
			perror("execve");
	}
	free_tab(cmd);
	close(vars->fd);
	close(vars->pipe[0][1]);
	return (0);
}

int	mid_cmd(t_vars *vars, char **env, int i)
{
	char	**cmd;

	if (pipe(vars->pipe[i]) == -1)
		return (-1);
	cmd = check_cmd(vars, vars->cmd[i]);
	if (cmd && access(cmd[0], F_OK | X_OK) != -1)
		vars->pid[i] = fork();
	if (vars->pid[i] == -1)
		return (-1);
	else if (vars->pid[i] == 0)
	{
		if (dup2(vars->pipe[i - 1][0], 0) == -1 || \
		dup2(vars->pipe[i][1], 1) == -1)
			return (-1);
		close(vars->pipe[i - 1][0]);
		close(vars->pipe[i][1]);
		close(vars->pipe[i][0]);
		if (execve(cmd[0], &cmd[0], env) == -1)
			perror("execve");
	}
	free_tab(cmd);
	close(vars->pipe[i - 1][0]);
	close(vars->pipe[i][1]);
	return (0);
}

int	last_cmd(t_vars *vars, int i, char **env)
{
	char	**cmd;
	int		fd;

	unlink(vars->outfile);
	fd = open(vars->outfile, O_CREAT | O_RDWR, S_IRWXU);
	cmd = check_cmd(vars, vars->cmd[i]);
	if (cmd && access(cmd[0], F_OK | X_OK) != -1 && fd != -1)
		vars->pid[i] = fork();
	if (vars->pid[i] == -1)
	{
		free_tab(cmd);
		return (-1);
	}
	else if (vars->pid[i] == 0)
	{
		if (dup2(vars->pipe[i - 1][0], 0) == -1 || \
		dup2(fd, 1) == -1)
			return (-1);
		close(vars->pipe[i - 1][0]);
		if (execve(cmd[0], &cmd[0], env) == -1)
			perror("execve");
	}
	free_tab(cmd);
	close(vars->pipe[i - 1][0]);
	return (0);
}

int	ft_unlink(t_vars *vars, int i)
{
	if (access(vars->outfile, R_OK) != -1)
		return (-1);
	else if (access(vars->outfile, F_OK))
		return (0);
	else if (unlink(vars->outfile) == -1)
		return (-1);
	(void)i;
	return (0);
}
