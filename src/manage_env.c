/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:11:33 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/19 17:07:27 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_node_with_str(char *str, t_list **env_lst)
{
	t_list	*node;

	str = ft_strdup(str);
	if (error_catch(str == NULL, "system", "Fail to malloc environment list"))
		return (ERROR);
	node = ft_lstnew(str);
	if (error_catch(node == NULL, "system", "Fail to malloc environment list"))
	{
		free(str);
		return (ERROR);
	}
	ft_lstadd_back(env_lst, node);
	return (SUCCESS);
}

static int	add_shlvl(t_list **node)
{
	char	*new_shlvl;
	char	*nb;

	nb = ft_itoa(ft_atoi(&((char *)(*node)->content)[6]) + 1);
	if (error_catch(nb == NULL, "system", "Malloc fail"))
		return (ERROR);
	new_shlvl = ft_strjoin("SHLVL=", nb);
	free(nb);
	if (error_catch(new_shlvl == NULL, "system", "Malloc fail"))
		return (ERROR);
	free((*node)->content);
	(*node)->content = new_shlvl;
	return (SUCCESS);
}

static int	update_shlvl(char **envp, t_root *root)
{
	t_list	*node;

	if (envp[0] == NULL)
	{
		if (add_node_with_str("SHLVL=1", &root->env) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	node = root->env;
	while (node)
	{
		if (ft_strncmp(node->content, "SHLVL=", 6) == 0)
			return (add_shlvl(&node));
		node = node->next;
	}
	return (FAIL);
}

static int	ft_loop_envp(char **envp, t_root *root)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (add_node_with_str(envp[i], &root->env) == ERROR)
		{
			ft_lstclear(&root->env, free);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	create_env(char **envp, t_root *root)
{
	char	*pwd;
	char	*env_pwd;

	root->env = NULL;
	if (ft_loop_envp(envp, root) == ERROR)
		return (ERROR);
	if (!envp[0] && add_node_with_str("PATH=/usr/local/bin:/usr/bin:/bin:\
/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki", &root->env) == ERROR)
		return (ERROR);
	pwd = ft_get_pwd();
	if (!pwd)
		return (ERROR);
	env_pwd = (char *)malloc(sizeof(char) * (5 + ft_strlen(pwd)));
	if (!env_pwd)
		return (ERROR);
	ft_strlcpy(env_pwd, "PWD=", 5);
	ft_strlcat(env_pwd, pwd, 5 + ft_strlen(pwd));
	if (!envp[0] && add_node_with_str(env_pwd, &root->env) == ERROR)
		return (ERROR);
	free(pwd);
	free(env_pwd);
	update_shlvl(envp, root);
	root->shell_env = NULL;
	return (SUCCESS);
}
