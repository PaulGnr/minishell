/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:40:46 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/22 08:40:47 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*dst;

	if (!s)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] && j < len && start < ft_strlen(s))
	{
		i++;
		j++;
	}
	dst = malloc(sizeof(char) * (j + 1));
	if (!dst)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] && j < len && start < ft_strlen(s))
		dst[j++] = s[i++];
	dst[j] = 0;
	return (dst);
}
