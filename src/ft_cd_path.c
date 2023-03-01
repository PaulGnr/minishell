/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:06:44 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/19 19:43:29 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_catch_cd(char *path, char *err_msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	free(path);
	return (1);
}

static int	ft_go_to_new_path(char *cdpath, char *path)
{
	char	*new_path;
	char	*pwd;

	new_path = (char *)malloc(sizeof(char) * (ft_strlen(cdpath)
				+ ft_strlen(path) + 2));
	if (error_catch(new_path == NULL, "system", "Malloc failed"))
	{
		free(path);
		return (1);
	}
	ft_strlcpy(new_path, cdpath, ft_strlen(cdpath) + 1);
	ft_strlcat(new_path, path, ft_strlen(cdpath) + ft_strlen(path) + 1);
	if (chdir(new_path) == -1)
	{
		free(new_path);
		return (1);
	}
	pwd = ft_get_pwd();
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	free(new_path);
	return (0);
}

int	ft_try_with_cdpath(t_list *env, char *path)
{
	while (env && ft_strncmp((char *)env->content, "CDPATH=", 7))
		env = env->next;
	if (!env)
		return (1);
	return (ft_go_to_new_path(&(((char *)(env->content))[7]), path));
}
