/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:39:36 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 16:22:06 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_double_free(char **s1, char **s2)
{
	ft_free_split(s1);
	return (ft_free_split_char(s2));
}

int	ft_add_back_split(char **dup, char **split, char *var, t_point p)
{
	char	**tmp;
	int		ret;

	tmp = ft_split(var, ' ');
	if (!tmp)
		return (0);
	dup[p.i] = ft_strjoin(tmp[0], &split[p.i][p.j + ft_strlen(var)]);
	if (!dup[p.i])
		return (ft_free_split(tmp));
	ret = ft_strlen(tmp[0]);
	ft_free_split(tmp);
	return (ret);
}

int	ft_add_front_split(char **dup, char **split, char *var, t_point p)
{
	char	**tmp;
	int		ret;

	tmp = ft_split(var, ' ');
	if (!tmp)
		return (0);
	dup[p.i] = (char *)malloc(sizeof(char) * (p.j + ft_strlen(tmp[0]) + 1));
	if (!dup[p.i])
		return (ft_free_split(tmp));
	ft_strlcpy(dup[p.i], split[p.i], p.j + 1);
	ft_strlcat(dup[p.i], tmp[0], p.j + ft_strlen(tmp[0]) + 1);
	ret = ft_strlen(tmp[0]);
	ft_free_split(tmp);
	return (ret);
}

int	ft_end_split(char ***dup, char **split, int i, int size)
{
	while (split[++i])
	{
		(*dup)[i + size - 1] = ft_strdup(split[i]);
		if (!(*dup)[i + size - 1])
			return (ft_free_split(*dup));
	}
	(*dup)[i + size - 1] = 0;
	return (1);
}

int	ft_end_new_split(char ***split, char **dup, int ret)
{
	ft_free_split(*split);
	*split = dup;
	return (ret);
}
