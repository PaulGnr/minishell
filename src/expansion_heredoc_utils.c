/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:50:06 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/15 17:50:59 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_str_heredoc(char *str, int pos, int size)
{
	char	*cpy;

	if (!str)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, str, pos + 1);
	ft_strlcat(cpy, &(str[pos + size]), ft_strlen(str) - size + 1);
	free(str);
	return (cpy);
}

char	*ft_insert_str_heredoc(char *s1, char *s2, int pos)
{
	char	*cpy;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cpy)
		return (NULL);
	cpy[0] = 0;
	ft_strlcpy(cpy, s1, pos + 1);
	ft_strlcat(cpy, s2, ft_strlen(cpy) + ft_strlen(s2) + 1);
	if (s1[pos])
		ft_strlcat(cpy, &(s1[pos]), ft_strlen(cpy) + ft_strlen(&(s1[pos])) + 1);
	free(s1);
	return (cpy);
}
