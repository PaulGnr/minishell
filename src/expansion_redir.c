/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:56:45 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/22 15:30:25 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove(char *str, int pos, int size)
{
	char	*cpy;

	if (!str)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	if (error_catch(!cpy, "system", "Malloc failed"))
		return (NULL);
	ft_strlcpy(cpy, str, pos + 1);
	ft_strlcat(cpy, &(str[pos + size]), ft_strlen(str) - size + 1);
	free(str);
	return (cpy);
}

static char	*ft_insert(char *s1, char *s2, int pos)
{
	char	*cpy;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (error_catch(!cpy, "system", "Malloc failed"))
		return (NULL);
	cpy[0] = 0;
	ft_strlcpy(cpy, s1, pos + 1);
	ft_strlcat(cpy, s2, ft_strlen(cpy) + ft_strlen(s2) + 1);
	if (s1[pos])
		ft_strlcat(cpy, &(s1[pos]), ft_strlen(cpy) + ft_strlen(&(s1[pos])) + 1);
	free(s1);
	return (cpy);
}

static char	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

static char	*ft_expansion_dollar(char *str, t_list *env, int *i)
{
	char	*var_name;
	char	*var;

	var_name = ft_get_var_name(&(str[*i + 1]));
	if (!var_name)
		return (ft_free(str));
	var = get_env(var_name, env);
	str = ft_remove(str, *i, ft_strlen(var_name) + 1);
	if (!str)
		return (ft_free(str));
	if (var)
	{
		str = ft_insert(str, var, *i);
		*i += ft_strlen(var) - 1;
		if (var_name[0] == '?')
			free(var);
		if (!str)
			return (ft_free(var_name));
	}
	else
		(*i)--;
	free(var_name);
	return (str);
}

char	*expansion_redir(char *str, t_list *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		ft_check_quote(str[i], &quote);
		if ((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1))
		{
			str = ft_remove(str, i--, 1);
			if (!str)
				return (NULL);
		}
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && quote != 1)
		{
			str = ft_expansion_dollar(str, env, &i);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
