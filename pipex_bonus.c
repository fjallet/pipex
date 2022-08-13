/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:16 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/13 15:47:04 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	vars_init(t_vars *vars, int argv, char **argc, char **env)
{
	vars->witness = 0;
	vars->argv = argv;
	vars->numcmd = argv - 3;
	vars->infile = argc[1];
	vars->outfile = argc[vars->argv - 1];
	vars->pid = 1;
	if (ft_strncmp(vars->infile, "here_doc", ft_strlen(vars->infile)) == 0)
		vars->numcmd--;
	if (ft_parsing(vars, argc) == -1)
		return (-1);
	if (setup_pipes(vars) == -1)
		return (-1);
	if (access(vars->infile, R_OK | F_OK) == -1 && \
	ft_strncmp(vars->infile, "here_doc", ft_strlen(vars->infile)) != 0)
		perror ("access");
	(void)env;
	return (0);
}

int	pipex(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(vars->infile, "here_doc", ft_strlen(vars->infile)) == 0)
		here_doc(vars);
	vars->fd = open(vars->infile, O_RDONLY);
	if (first_cmd(vars, env) == -1)
		return (-1);
	if (vars->fd == -1)
		close(vars->pipe[0][1]);
	if (ft_strncmp(vars->infile, "here_doc", ft_strlen(vars->infile)) == 0)
		unlink(vars->infile);
	while (++i < vars->numcmd)
	{
		if (mid_cmd(vars, env, i) == -1)
			return (-1);
	}
	if (last_cmd(vars, i - 1) == -1)
		return (-1);
	return (0);
}

void	here_doc(t_vars *vars)
{
	int		fd;
	char	*str;

	fd = open(vars->infile, O_CREAT | O_RDWR, S_IRWXU);
	while (fd != -1)
	{
		str = NULL;
		write(1, ">>", 2);
		str = get_next_line(0, 0);
		if (ft_strncmp(str, vars->limiter, ft_strlen(str) - 1) == 0)
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	get_next_line(0, 1);
	free(str);
	close(fd);
}

int	main(int argv, char **argc, char **env)
{
	t_vars	vars;

	if (argv < 5)
		return (0);
	if (ft_path(&vars, env) == -1)
		return (0);
	if (vars_init(&vars, argv, argc, env) == -1)
	{
		free_all(&vars);
		return (0);
	}
	if (pipex(&vars, env) == -1)
	{
		free_all(&vars);
		return (0);
	}
	free_all(&vars);
	return (0);
}
