/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:54:01 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/19 15:32:21 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_path_pwd(char *path, char *pwd)
{
	free(path);
	if (pwd)
		free(pwd);
	return (1);
}

static int	ft_no_oldpwd(t_root *root, char *content)
{
	t_list	*new;

	new = ft_lstnew((void *)content);
	if (error_catch(new == NULL, "system", "Malloc failed"))
	{
		free(content);
		return (0);
	}
	ft_lstlast(root->env)->next = new;
	return (1);
}

int	ft_no_pwd(t_root *root)
{
	t_list	*env;
	char	*pwd;
	char	*old_pwd;

	env = root->env;
	while (env && ft_strncmp((char *)env->content, "PWD=", 4))
		env = env->next;
	if (env)
		return (1);
	pwd = ft_get_pwd();
	if (error_catch(pwd == NULL, "system", "Malloc failed"))
		return (!free_path_pwd(pwd, NULL));
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (error_catch(old_pwd == NULL, "system", "Malloc failed"))
		return (!free_path_pwd(pwd, NULL));
	free(pwd);
	env = root->env;
	while (env && ft_strncmp((char *)env->content, "OLDPWD=", 7))
		env = env->next;
	if (!env)
		return (ft_no_oldpwd(root, old_pwd));
	free(env->content);
	env->content = (void *)old_pwd;
	return (-1);
}

static int	ft_add_oldpwd(t_root *root)
{
	t_list	*env;
	char	*content;

	env = root->env;
	while (env && ft_strncmp((char *)env->content, "PWD=", 4))
		env = env->next;
	if (!env)
		return (1);
	content = ft_strjoin("OLDPWD=", &(((char *)env->content)[4]));
	if (!content)
		return (0);
	env = root->env;
	while (env && ft_strncmp((char *)env->content, "OLDPWD=", 7))
		env = env->next;
	if (!env)
		return (ft_no_oldpwd(root, content));
	else
	{
		free(env->content);
		env->content = (void *)content;
	}
	return (1);
}

int	ft_modify_pwd(t_root *root, char *path)
{
	t_list	*env;
	char	*content;
	char	*pwd;

	pwd = ft_get_pwd();
	if (error_catch(pwd == NULL, "system", "Malloc failed"))
		return (free_path_pwd(path, pwd));
	if (error_catch(ft_add_oldpwd(root) == 0, "system", "Malloc failed"))
		return (free_path_pwd(path, pwd));
	env = root->env;
	while (env && ft_strncmp((char *)env->content, "PWD=", 4))
		env = env->next;
	if (!env)
		return (!free_path_pwd(path, pwd));
	if ((path && !ft_strncmp(path, "//", 2) && ft_strncmp(path, "///", 3))
		|| (!ft_strncmp(&(((char *)env->content)[4]), "//", 2)
		&& ft_strncmp(path, "/", 1)))
		content = ft_strjoin("PWD=/", pwd);
	else
		content = ft_strjoin("PWD=", pwd);
	if (error_catch(content == NULL, "system", "Malloc failed"))
		return (free_path_pwd(pwd, path));
	free_path_pwd(pwd, (char *)env->content);
	env->content = (void *)content;
	return (0);
}
