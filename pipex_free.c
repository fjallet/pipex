/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:02:15 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/05 17:27:18 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_vars *vars)
{
	free_tab(vars->cmd);
	free_tab(vars->paths);
	if (vars->witness == 1)
		free_tab_int(vars->pipe, vars->numcmd);
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tab_int(int **tab, int taille)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < taille)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
