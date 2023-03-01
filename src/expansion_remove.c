/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:32:04 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 17:45:26 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_begin_add_split(char **split, int pos)
{
	char	**new_split;
	int		i;

	new_split = (char **)malloc(sizeof(char *) * (split_size(split) + 2));
	if (!new_split)
		return (ft_free_split_char(split));
	i = 0;
	while (i < pos)
	{
		new_split[i] = ft_strdup(split[i]);
		if (!new_split[i++])
			return (ft_double_free(split, new_split));
	}
	new_split[i] = ft_strdup("");
	if (!new_split[i++])
		return (ft_double_free(split, new_split));
	return (new_split);
}

static char	**ft_add_empty_case(char **split, int pos)
{
	char	**new_split;
	int		i;

	new_split = ft_begin_add_split(split, pos);
	if (error_catch(!new_split, "system", "Malloc failed"))
		return (NULL);
	i = pos + 1;
	while (split[i - 1])
	{
		new_split[i] = ft_strdup(split[i - 1]);
		if (error_catch(!new_split[i++], "system", "Malloc failed"))
			return (ft_double_free(split, new_split));
	}
	new_split[i] = 0;
	ft_free_split(split);
	return (new_split);
}

char	**ft_remove_quote(char **split, t_point *p, int quote, t_list *env)
{
	char	*var_name;
	char	*var;

	split[p->i] = ft_remove_str(split, split[p->i], p->j, 1);
	if (!split[p->i])
		return (NULL);
	if (split[p->i][p->j] != '$' || quote || p->j)
	{
		p->j--;
		return (split);
	}
	var_name = ft_get_var_name(&(split[p->i][p->j + 1]));
	var = get_env(var_name, env);
	free(var_name);
	if (!var || var[0] != ' ')
		return (split);
	if (var[0] == '?')
		free(var);
	split = ft_add_empty_case(split, p->i++);
	p->j = -1;
	return (split);
}

char	**ft_remove_case(char **split, int pos, char *var_name)
{
	char	**new_split;
	int		i;

	free(var_name);
	new_split = (char **)malloc(sizeof(char *) * split_size(split));
	if (!new_split)
		return (ft_free_split_char(split));
	i = 0;
	while (i < pos)
	{
		new_split[i] = ft_strdup(split[i]);
		if (!new_split[i++])
			return (ft_double_free(split, new_split));
	}
	while (split[++i])
	{
		new_split[i - 1] = ft_strdup(split[i]);
		if (!new_split[i - 1])
			return (ft_double_free(split, new_split));
	}
	new_split[i - 1] = 0;
	ft_free_split(split);
	return (new_split);
}
