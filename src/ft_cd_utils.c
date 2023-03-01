/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:45 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/20 14:22:57 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_home_path(t_list *env)
{
	char	*path;

	while (env && ft_strncmp(env->content, "HOME=", 5))
		env = env->next;
	if (!env)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	path = (char *)malloc(sizeof(char)
			* (ft_strlen(&(((char *)(env->content))[5])) + 1));
	if (!path)
	{
		ft_putstr_fd("minishell: system: Malloc failed\n", 2);
		return (NULL);
	}
	ft_strlcpy(path, &(((char *)(env->content))[5]),
		ft_strlen(&(((char *)(env->content))[5])) + 1);
	return (path);
}

static char	*ft_concate_home_path(char *str, t_list *env)
{
	char	*path;

	while (env && ft_strncmp(env->content, "HOME=", 5))
		env = env->next;
	if (!env)
	{
		path = ft_strdup(str);
		if (error_catch(path == NULL, "system", "Malloc failed"))
			return (NULL);
		return (path);
	}
	path = (char *)malloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(&(((char *)(env->content))[5]))));
	if (!path)
		return (NULL);
	ft_strlcpy(path, &(((char *)(env->content))[5]),
		ft_strlen(&(((char *)(env->content))[5])) + 1);
	ft_strlcat(path, &(str[1]), ft_strlen(path) + ft_strlen(str));
	return (path);
}

char	*ft_get_path(char *str, t_list *env)
{
	char	*path;

	if (!ft_strncmp(str, "--", 3))
		return (ft_get_home_path(env));
	else if (!ft_strncmp(str, "~/", 2))
		return (ft_concate_home_path(str, env));
	else if (!ft_strncmp(str, "-", 2) || !ft_strncmp(str, "~-", 3))
	{
		while (env && ft_strncmp(env->content, "OLDPWD=", 7))
			env = env->next;
		if (error_catch(env == NULL, "cd", "OLDPWD not set"))
			return (NULL);
		return (ft_strdup(&(((char *)(env->content))[7])));
	}
	else
	{
		path = ft_strdup(str);
		if (error_catch(path == NULL, "system", "Malloc failed"))
			return (NULL);
	}
	return (path);
}
