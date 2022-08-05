/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:30:19 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/05 17:25:33 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"
# include <errno.h>  
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_vars
{
	char	*infile;
	char	*outfile;
	char	**cmd;
	char	**paths;
	int		**pipe;
	int		fd;
	int		argv;
	int		numcmd;
	pid_t	pid;
	int		witness;
}				t_vars;

//pipex_parsing
void	ft_parsing(t_vars *vars, char **argc);
char	*ft_fullpath(char *path, char *file);
void	ft_path(t_vars *vars, char **env);
char	**check_cmd(t_vars *vars, char *cmd);
int		setup_pipes(t_vars *vars);

//pippex_str
size_t	ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strlcpy(char *dst, char *src);

//split
char	**ft_split(char const *s, char c);

//pipex_free
void	free_all(t_vars *vars);
void	free_tab(char **str);
void	free_tab_int(int **tab, int taille);

//pipex_exe
int		first_cmd(t_vars *vars, char **env);
int		mid_cmd(t_vars *vars, char **env, int i);
int		last_cmd(t_vars *vars, int i);

//pipex
int		vars_init(t_vars *vars, int argv, char **argc, char **env);
int		pipex(t_vars *vars, char **env);

#endif