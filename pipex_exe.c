/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:49:44 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/08 16:36:58 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(t_vars *vars, char **env)
{	
	char	**cmd;

	if (pipe(vars->pipe[0]) == -1)
		return (-1);
	vars->pid = fork();
	cmd = check_cmd(vars, vars->cmd[0]);
	if (vars->pid == -1 || !cmd || vars->fd == -1)
		return (-1);
	else if (vars->pid == 0)
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
	//wait(NULL);
	return (0);
}

int	mid_cmd(t_vars *vars, char **env, int i)
{
	char	**cmd;

	if (pipe(vars->pipe[i]) == -1)
		return (-1);
	vars->pid = fork();
	cmd = check_cmd(vars, vars->cmd[i]);
	if (vars->pid == -1 || !cmd)
		return (-1);
	else if (vars->pid == 0)
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
	//wait(NULL);
	return (0);
}

int	last_cmd(t_vars *vars, int i)
{
	int		fd;
	int		num;
	char	buf[1000];

	num = 1000;
	if (ft_strncmp(vars->infile, "here_doc", 8) != 0)
		unlink(vars->outfile);
	fd = open(vars->outfile, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
		return (-1);
	num = 1000;
	while (num == 1000)
		num = read(fd, buf, 1000);
	num = 1000;
	while (num > 0)
	{
		num = read(vars->pipe[i][0], buf, 1000);
		write(fd, buf, num);
	}
	close(vars->pipe[i][0]);
	close(fd);
	return (0);
}
