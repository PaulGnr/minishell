/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:26:43 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 14:57:41 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

static char	*ft_expansion_var_heredoc(char *split, char *var, int *i)
{
	split = ft_insert_str_heredoc(split, var, *i);
	if (!split)
		return (NULL);
	*i += ft_strlen(var) - 1;
	return (split);
}

static char	*ft_expansion_dollar(char *split, t_list *env, int *i)
{
	char	*var_name;
	char	*var;

	var_name = ft_get_var_name(&(split[*i + 1]));
	if (!var_name)
		return (ft_free(split));
	var = get_env(var_name, env);
	split = ft_remove_str_heredoc(split, *i, ft_strlen(var_name) + 1);
	if (!split)
		return (ft_free(split));
	if (var)
	{
		split = ft_expansion_var_heredoc(split, var, i);
		if (var_name[0] == '?')
			free(var);
		if (!split)
			return (NULL);
	}
	else
		(*i)--;
	free(var_name);
	return (split);
}

static char	*ft_expansion_loop(char *split, t_list *env, int quote, int *i)
{
	if (split[*i] == '$' && quote != 1)
	{
		split = ft_expansion_dollar(split, env, i);
		if (!split)
			return (NULL);
	}
	(*i)++;
	return (split);
}

char	*ft_expansion_heredoc(char *split, t_list *env)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (split[i])
	{
		ft_check_quote(split[i], &quote);
		split = ft_expansion_loop(split, env, quote, &i);
		if (!split)
			return (NULL);
	}
	if (split[i])
		i++;
	return (split);
}
