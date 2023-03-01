/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:47:25 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/18 19:47:28 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_malloc(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		return (s2);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = ft_strlen(s1);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	j = 0;
	if (!s1)
		while (s2[j] == ' ')
			j++;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	free(s1);
	free(s2);
	return (join);
}
