/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:55:53 by fjallet           #+#    #+#             */
/*   Updated: 2022/08/08 15:40:55 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
/*size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}*/

size_t	ft_strchrlen(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		i++;
	return (i);
}

char	*ft_strjoin(char *old, char *src)
{
	size_t	i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(old) + ft_strlen(src) + 1));
	if (!new)
		return (0);
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	i = 0;
	while (src[i] != '\0')
	{
		new[i + ft_strlen(old)] = src[i];
		i++;
	}
	new[i + ft_strlen(old)] = '\0';
	if (old)
		free(old);
	return (new);
}

char	*ft_strtrim1(char *old)
{
	size_t	i;
	char	*new;

	if (!old)
		return (ft_strdup(""));
	i = 0;
	new = malloc(sizeof(char) * (ft_strchrlen(old, '\n') + 1));
	if (!new)
		return (0);
	while (i < ft_strchrlen(old, '\n'))
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strtrim2(char *old)
{
	size_t	i;
	char	*new;

	if (!old)
		return (ft_strdup(""));
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(old) - ft_strchrlen(old, '\n') + 1));
	if (!new)
		return (0);
	while (i < ft_strlen(old) - ft_strchrlen(old, '\n'))
	{
		new[i] = old[ft_strchrlen(old, '\n') + i];
		i++;
	}
	new[i] = '\0';
	if (old)
		free(old);
	return (new);
}
