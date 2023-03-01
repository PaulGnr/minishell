/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:27:31 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/21 16:27:40 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	limdef(int start, int end)
{
	if (end == 0)
		end = start;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		lim[2];
	char	*dst;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && is_set(set, s1[i]))
		i++;
	lim[0] = i;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && is_set(set, s1[i]))
		i--;
	lim[1] = i + 1;
	lim[1] = limdef(lim[0], lim[1]);
	dst = malloc(sizeof(char) * (lim[1] - lim[0] + 1));
	if (!dst)
		return (NULL);
	i = lim[0];
	j = 0;
	while (i < lim[1])
		dst[j++] = s1[i++];
	dst[j] = 0;
	return (dst);
}
