/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:28:43 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 16:22:09 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_split_expansion(char ***new_split, char **split, int j, int k)
{
	(*new_split)[k] = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*new_split)[k])
		return (0);
	ft_strlcpy((*new_split)[k], split[k], j + 1);
	(*new_split)[k + 1] = ft_strdup(&(split[k][j]));
	if (!(*new_split)[k + 1])
		return (0);
	return (1);
}

char	**ft_new_split_expansion(char **split, int i, int j)
{
	char	**new_split;
	int		k;

	new_split = (char **)malloc(sizeof(char *) * (split_size(split) + 2));
	if (!new_split)
		return (ft_free_split_char(split));
	k = 0;
	while (k < i)
	{
		new_split[k] = ft_strdup(split[k]);
		if (!new_split[k++])
			return (ft_double_free(split, new_split));
	}
	if (!ft_add_split_expansion(&new_split, split, j, k))
		return (ft_double_free(split, new_split));
	while (split[++k])
	{
		new_split[k + 1] = ft_strdup(split[k]);
		if (!new_split[k + 1])
			return (ft_double_free(split, new_split));
	}
	new_split[k + 1] = 0;
	ft_free_split(split);
	return (new_split);
}

static int	ft_add_split(char **dup, char **split, char *var, t_point p)
{
	char	**tmp;
	int		i;
	int		ret;

	tmp = ft_split(var, ' ');
	if (!tmp)
		return (0);
	dup[p.i] = (char *)malloc(sizeof(char) * (p.j + ft_strlen(tmp[0]) + 1));
	if (!dup[p.i])
		return (ft_free_split(tmp));
	ft_strlcpy(dup[p.i], split[p.i], p.j + 1);
	ft_strlcat(dup[p.i], tmp[0], p.j + ft_strlen(tmp[0]) + 1);
	i = 1;
	while (tmp[i + 1])
	{
		dup[p.i + i] = ft_strdup(tmp[i]);
		if (!dup[p.i + i++])
			return (ft_free_split(tmp));
	}
	dup[p.i + i] = ft_strjoin(tmp[i], &split[p.i][p.j + ft_strlen(var)]);
	if (!dup[p.i + i])
		return (ft_free_split(tmp));
	ret = ft_strlen(tmp[i]);
	ft_free_split(tmp);
	return (ret);
}

static char	**ft_begin_new_split(char **split, t_point p, int size)
{
	char	**dup;
	int		i;

	dup = (char **)malloc(sizeof(char *) * (split_size(split) + size));
	if (!dup)
		return (ft_free_split_char(split));
	i = 0;
	while (i < p.i)
	{
		dup[i] = ft_strdup(split[i]);
		if (!dup[i++])
			return (ft_double_free(dup, split));
	}
	return (dup);
}

int	ft_new_split(char ***split, t_point p, char *var, int size)
{
	char	**dup;
	int		i;
	int		ret;

	dup = ft_begin_new_split(*split, p, size);
	if (!dup)
		return (0);
	i = p.i;
	if (size > 1)
		ret = ft_add_split(dup, *split, var, p);
	else if (var[0] == ' ')
		ret = ft_add_back_split(dup, *split, var, p);
	else if (var[ft_strlen(var) - 1] == ' ')
		ret = ft_add_front_split(dup, *split, var, p);
	else
	{
		ret = ft_strlen(var);
		i--;
	}
	if (!ret)
		return (ft_free_split(dup));
	if (!ft_end_split(&dup, *split, i, size))
		return (0);
	return (ft_end_new_split(split, dup, ret));
}
