/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:40:02 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/08 16:13:01 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_endfree(char *rst)
{
	if (rst)
	{
		free(rst);
		rst = NULL;
	}
	return (1);
}

size_t	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((sizeof(char)) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_next_line(int fd, int clear)
{
	int			bs;
	char		*str;
	static char	*rst = NULL;
	char		buf[101];

	bs = 100;
	if (clear == 1 && ft_endfree(rst))
		return (NULL);
	while (ft_strchr(rst, '\n') == 0 && bs == 100)
	{
		bs = read(fd, buf, 100);
		if (bs < 0 || fd < 0 || fd > 1024 || 100 < 1)
			return (NULL);
		if (bs == 0 && ft_strlen(rst) == 0 && ft_endfree(rst))
			return (NULL);
		buf[bs] = '\0';
		rst = ft_strjoin(rst, buf);
	}
	str = ft_strtrim1(rst);
	rst = ft_strtrim2(rst);
	return (str);
}
