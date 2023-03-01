/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:50:01 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/22 15:07:25 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_str(char **split, char *str, int pos, int size)
{
	char	*cpy;

	if (!str)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	if (error_catch(!cpy, "system", "Malloc failed"))
	{
		ft_free_split(split);
		return (NULL);
	}
	ft_strlcpy(cpy, str, pos + 1);
	ft_strlcat(cpy, &(str[pos + size]), ft_strlen(str) - size + 1);
	free(str);
	return (cpy);
}

char	*ft_insert_str(char **split, char *s1, char *s2, int pos)
{
	char	*cpy;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (error_catch(!cpy, "system", "Malloc failed"))
	{
		ft_free_split(split);
		return (NULL);
	}
	cpy[0] = 0;
	ft_strlcpy(cpy, s1, pos + 1);
	ft_strlcat(cpy, s2, ft_strlen(cpy) + ft_strlen(s2) + 1);
	if (s1[pos])
		ft_strlcat(cpy, &(s1[pos]), ft_strlen(cpy) + ft_strlen(&(s1[pos])) + 1);
	free(s1);
	return (cpy);
}

char	*ft_get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while ((*str != '?' && (ft_isalnum(str[i]) || str[i] == '_'))
		|| (*str == '?' && i == 0))
		i++;
	var = (char *)malloc(sizeof(char) * (i + 1));
	if (error_catch(!var, "system", "Malloc failed"))
		return (NULL);
	i = 0;
	while ((*str != '?' && (ft_isalnum(str[i]) || str[i] == '_'))
		|| (*str == '?' && i == 0))
	{
		var[i] = str[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

char	*get_env(char *var_name, t_list *env)
{
	char	*var;

	if (var_name[0] == '?')
		return (ft_itoa(g_exit_status));
	while (env && (ft_strncmp(var_name, env->content, ft_strlen(var_name))
			|| ((char *)env->content)[ft_strlen(var_name)] != '='))
		env = env->next;
	if (env && env->content)
	{
		var = &((char *)env->content)[ft_strlen(var_name) + 1];
		return (var);
	}
	else
		return (NULL);
}

int	ft_size_var(char *var)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (var[i] == ' ')
		i++;
	while (var[i])
	{
		if ((i == 0 && var[i] != ' ')
			|| (i != 0 && var[i] != ' ' && var [i - 1] == ' '))
			size++;
		i++;
	}
	return (size);
}
