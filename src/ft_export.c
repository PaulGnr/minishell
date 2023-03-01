/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:11:47 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/25 18:57:52 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_forbidden_char(char *to_export)
{
	long	i;

	if (ft_isdigit(to_export[0]))
		return (FAIL);
	i = 0;
	while (to_export[i] && to_export[i] != '=')
	{
		if (!ft_isalnum(to_export[i++]))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	parse_identifier(char *to_export, char **equal_addr, int *status)
{
	*equal_addr = ft_strchr(to_export, '=');
	if (not_a_valid_identifier(to_export[0] == 0
			|| check_forbidden_char(to_export) == FAIL,
			"export", to_export))
	{
		*status = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

static int	find_identifier(long identifier_len, char *to_export, t_root *root)
{
	t_list	*node;

	node = root->env;
	if (identifier_len < 0)
		identifier_len = (long)ft_strlen(to_export);
	while (node)
	{
		if (!ft_strncmp(to_export, node->content, identifier_len)
			&& !to_export[identifier_len]
			&& ((char *)node->content)[identifier_len] == '=')
			return (SUCCESS);
		if (ft_strncmp(to_export, node->content, identifier_len + 1) == 0
			|| (ft_strncmp(to_export, node->content, identifier_len) == 0
				&& to_export[identifier_len] == '='))
		{
			free(node->content);
			node->content = ft_strdup(to_export);
			if (error_catch(node->content == NULL, "system", "Malloc fail"))
				return (ERROR);
			return (SUCCESS);
		}
		node = node->next;
	}
	return (FAIL);
}

static int	add_identifier(char *to_export, t_root *root)
{
	char	*content;
	t_list	*node;

	content = ft_strdup(to_export);
	if (error_catch(content == NULL, "system", "Malloc fail"))
		return (ERROR);
	node = ft_lstnew(content);
	if (error_catch(node == NULL, "system", "Malloc fail"))
		return (ERROR);
	ft_lstadd_back(&root->env, node);
	return (SUCCESS);
}

int	ft_export(t_cmd *cmd, t_root *root)
{
	char	*equal_addr;
	int		is_find;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (cmd->split_cmd[++i])
	{
		if (parse_identifier(cmd->split_cmd[i], &equal_addr, &status) == FAIL)
			continue ;
		is_find = find_identifier(equal_addr - cmd->split_cmd[i],
				cmd->split_cmd[i], root);
		if (is_find == ERROR || is_find == SUCCESS)
			continue ;
		else
			add_identifier(cmd->split_cmd[i], root);
	}
	if (i == 1)
		export_without_arg(root->env->next, cmd);
	return (status);
}
