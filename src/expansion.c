/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:15:37 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 17:45:44 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_expansion_dollar(char **split, t_list *env, t_point *p,
		int quote)
{
	char	*var_name;
	char	*var;

	var_name = ft_get_var_name(&(split[p->i][p->j + 1]));
	if (!var_name)
		return (ft_free_split_char(split));
	var = get_env(var_name, env);
	if (p->j == 0 && ft_strlen(var_name) + 1 == ft_strlen(split[p->i]) && !var)
		return (ft_remove_case(split, p->i--, var_name));
	split[p->i] = ft_remove_str(split, split[p->i], p->j,
			ft_strlen(var_name) + 1);
	if (!split[p->i])
		return (ft_free_split_char(split));
	if (var)
	{
		split = ft_expansion_var(split, var, p, quote);
		if (var_name[0] == '?')
			free(var);
		if (!split)
			return (NULL);
	}
	else
		p->j--;
	free(var_name);
	return (split);
}

static char	**ft_expansion_tilde(char **split, t_list *env, t_point *p)
{
	while (env && ft_strncmp((char *)env->content, "HOME=", 5))
		env = env->next;
	if (!env)
		return (split);
	split[p->i] = ft_remove_str(split, split[p->i], p->j, 1);
	if (!split[p->i])
		return (ft_free_split_char(split));
	split[p->i] = ft_insert_str(split, split[p->i],
			&(((char *)(env->content))[5]), p->j);
	if (!split[p->i])
		return (ft_free_split_char(split));
	return (split);
}

static char	**ft_expansion_loop(char **split, t_list *env, int quote,
		t_point *p)
{
	if ((split[p->i][p->j] == '\'' && quote != 2)
			|| (split[p->i][p->j] == '\"' && quote != 1))
	{
		split = ft_remove_quote(split, p, quote, env);
		if (!split)
			return (NULL);
	}
	else if (!quote && split[p->i][p->j] == '~' && p->j == 0
		&& (!split[p->i][p->j + 1] || split[p->i][p->j + 1] == '/'))
	{
		split = ft_expansion_tilde(split, env, p);
		if (!split)
			return (NULL);
	}
	else if (split[p->i][p->j] == '$' && split[p->i][p->j + 1]
			&& split[p->i][p->j + 1] != '$' && quote != 1)
	{
		split = ft_expansion_dollar(split, env, p, quote);
		if (!split)
			return (NULL);
	}
	p->j++;
	return (split);
}

char	**ft_expansion(char **split, t_list *env)
{
	int		quote;
	t_point	p;

	quote = 0;
	p.i = 0;
	while (split[p.i])
	{
		p.j = 0;
		while (p.i >= 0 && split[p.i] && split[p.i][p.j])
		{
			ft_check_quote(split[p.i][p.j], &quote);
			split = ft_expansion_loop(split, env, quote, &p);
			if (!split)
				return (NULL);
		}
		if (p.i < 0 || split[p.i])
			p.i++;
	}
	return (split);
}
