/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:29:56 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/25 18:39:59 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_forbidden_char(char *to_unset)
{
	long	i;

	i = 0;
	while (to_unset[i])
	{
		if (!ft_isalnum(to_unset[i++]))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	parse_identifier(char *to_unset, int *status)
{
	if (not_a_valid_identifier(ft_strchr(to_unset, '=') != NULL
			|| to_unset[0] == 0 || check_forbidden_char(to_unset) == FAIL,
			"unset", to_unset))
	{
		*status = 1;
		return (FAIL);
	}
	return (SUCCESS);
}

static void	find_identifier(char *to_unset, t_root *root)
{
	t_list	*temp;
	t_list	*node;

	node = root->env;
	while (node->next)
	{
		if (ft_strncmp(to_unset, node->next->content, ft_strlen(to_unset)) == 0
			&& (((char *)node->next->content)[ft_strlen(to_unset)] == '='
			|| ((char *)node->next->content)[ft_strlen(to_unset)] == 0))
		{
			temp = node->next->next;
			ft_lstdelone(node->next, free);
			node->next = temp;
			return ;
		}
		node = node->next;
	}
}

int	ft_unset(t_cmd *cmd, t_root *root)
{
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (cmd->split_cmd[++i])
	{
		if (parse_identifier(cmd->split_cmd[i], &status) == FAIL)
			continue ;
		find_identifier(cmd->split_cmd[i], root);
	}
	return (status);
}
