/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:00:09 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/12 18:48:21 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_strs(char **strs, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (0);
}

static int	nb_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	strclen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(const char *str, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	strs = malloc(sizeof(char *) * (nb_words(str, c) + 1));
	if (!strs)
		return (NULL);
	while (nb_words(str, c) > 0)
	{
		while (*str && *str == c)
			str++;
		j = strclen(str, c);
		strs[i] = malloc(j + 1);
		if (!strs[i])
			return (free_strs(strs, i));
		j = 0;
		while (*str && *str != c)
			strs[i][j++] = *str++;
		strs[i++][j] = 0;
	}
	strs[i] = 0;
	return (strs);
}
