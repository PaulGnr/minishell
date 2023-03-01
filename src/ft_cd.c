/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:41:29 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/19 19:42:40 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_no_arg(t_root *root)
{
	int		retval;
	t_list	*env;

	env = root->env;
	while (env && ft_strncmp(env->content, "HOME=", 5))
		env = env->next;
	if (!env)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	retval = 0;
	if (((char *)env->content)[5])
		retval = chdir(&(((char *)(env->content))[5]));
	if (retval == -1)
		return (error_catch_cd(&((char *)env->content)[5], strerror(errno)));
	return (ft_modify_pwd(root, NULL));
}

static int	ft_cd_one_arg(t_cmd *cmd, t_root *root)
{
	char	*path;
	int		pwd;

	path = ft_get_path(cmd->split_cmd[1], root->env);
	if (!path)
		return (1);
	if (!path[0])
		return (!free_path_pwd(path, NULL));
	pwd = ft_no_pwd(root);
	if (!pwd)
		return (!free_path_pwd(path, NULL));
	if (ft_strncmp(path, "/", 1) && ft_strncmp(path, ".", 2)
		&& ft_strncmp(path, "..", 3)
		&& ft_try_with_cdpath(root->env, path) && chdir(path) == -1)
		return (error_catch_cd(path, strerror(errno)));
	else if ((!ft_strncmp(path, "/", 1) || !ft_strncmp(path, ".", 2)
			|| !ft_strncmp(path, "..", 3)) && chdir(path) == -1)
		return (error_catch_cd(path, strerror(errno)));
	if (!ft_strncmp(cmd->split_cmd[1], "-", 2))
		printf("%s\n", path);
	if (pwd > -1 && ft_modify_pwd(root, path))
		return (1);
	return (!free_path_pwd(path, NULL));
}

int	ft_cd(t_cmd *cmd, t_root *root)
{
	if (split_size(cmd->split_cmd) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->split_cmd[1])
		return (ft_cd_one_arg(cmd, root));
	else
		return (ft_cd_no_arg(root));
	return (0);
}
