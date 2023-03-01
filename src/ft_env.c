/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:00:42 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/25 18:35:21 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_root *root)
{
	t_list	*env_lst;

	env_lst = root->env;
	while (env_lst)
	{
		if (ft_strchr(env_lst->content, '='))
		{
			ft_putstr_fd(env_lst->content, cmd->fd_out);
			ft_putchar_fd('\n', cmd->fd_out);
		}
		env_lst = env_lst->next;
	}
	return (0);
}
