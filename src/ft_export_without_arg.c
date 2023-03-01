/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_without_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:53:16 by sgaubert          #+#    #+#             */
/*   Updated: 2021/09/22 13:53:18 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_lst(t_list *lst)
{
	t_list	*node;
	char	*temp;
	t_bool	is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		node = lst;
		while (node->next)
		{
			if (ft_strncmp(node->content, node->next->content,
					ft_strlen(node->content)) > 0)
			{
				temp = node->content;
				node->content = node->next->content;
				node->next->content = temp;
				is_sorted = 0;
			}
			node = node->next;
		}
	}
}

static void	print_lst(t_list *lst, int fd)
{
	while (lst)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(lst->content, fd);
		ft_putstr_fd("\n", fd);
		lst = lst->next;
	}
}

int	export_without_arg(t_list *env, t_cmd *cmd)
{
	t_list	*newlst;

	newlst = ft_lstmap(env, (void *(*)(void *))ft_strdup, free);
	if (error_catch(newlst == NULL, "system", "Malloc fail"))
		return (ERROR);
	sort_lst(newlst);
	print_lst(newlst, cmd->fd_out);
	ft_lstclear(&newlst, free);
	return (SUCCESS);
}
