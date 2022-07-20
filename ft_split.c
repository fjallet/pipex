/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:04:16 by fjallet           #+#    #+#             */
/*   Updated: 2022/07/20 12:39:42 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	ft_splitfree(char **str, size_t j)
{
	while (j > 0 && str[j])
	{
		j--;
		free(str[j]);
	}
	free(str);
}

static size_t	ft_countchar(char const *s, char c, size_t j)
{
	size_t	i;

	i = j;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_puttr(char const *s, size_t c, size_t j, char **str)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (c + 1));
	if (!res)
	{
		ft_splitfree(str, j);
		return (0);
	}
	while (i < c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static size_t	ft_countw(char const *s, char c)
{
	size_t	i;
	size_t	t;
	size_t	count;

	i = 0;
	t = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			t = 1;
		else if (s[i] != c && t == 1)
		{
			count++;
			t = 0;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (ft_countw(s, c) + 1));
	if (!res)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			res[j] = ft_puttr(&s[i], ft_countchar(&s[i], c, j), j, res);
			if (!res)
				return (0);
			i += ft_countchar(&s[i], c, j++);
		}
	}
	res[j] = 0;
	return (res);
}
