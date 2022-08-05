/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:29:16 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/05 17:30:03 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	vars_init(t_vars *vars, int argv, char **argc, char **env)
{
	vars->witness = 0;
	vars->argv = argv;
	vars->numcmd = argv - 3;
	ft_parsing(vars, argc);
	ft_path(vars, env);
	if (setup_pipes(vars) == -1)
		return (-1);
	return (0);
}

int	pipex(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	while (i < vars->numcmd)
	{
		if (i == 0)
		{
			if (first_cmd(vars, env) == -1)
				return (-1);
		}
		if (i != 0 && i < vars->numcmd)
		{
			if (mid_cmd(vars, env, i) == -1)
				return (-1);
		}
		i++;
	}
	if (last_cmd(vars, i - 1) == -1)
		return (-1);
	return (0);
}

int	main(int argv, char **argc, char **env)
{
	t_vars	vars;

	if (vars_init(&vars, argv, argc, env) == -1)
	{
		free_all(&vars);
		return (-1);
	}
	if (pipex(&vars, env) == -1)
	{
		free_all(&vars);
		return (-1);
	}
	free_all(&vars);
}
