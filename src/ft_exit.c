/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:45:21 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/20 15:51:42 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	exit_error(char *str)
{
	ft_putstr_fd("minishell: exit :", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(":numeric argument required\n", 2);
}

int	ft_exit(t_cmd *cmd, t_root *root)
{
	if (g_exit_status == -1)
		g_exit_status = 0;
	if (root->nb_of_cmd == 1)
		ft_putstr_fd("exit\n", 1);
	if (cmd->split_cmd[1] && !ft_is_all_num(cmd->split_cmd[1]))
	{
		exit_error(cmd->split_cmd[1]);
		g_exit_status = 2;
	}
	else if (cmd->split_cmd[1])
	{
		g_exit_status = ft_atoi(cmd->split_cmd[1]);
		if (cmd->split_cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	close_fd(cmd->redir);
	close_pipe(root->pipe_fd, root->nb_of_cmd);
	free_split_cmd(root->cmds, root->nb_of_cmd);
	ft_free_cmds(root->cmds, root);
	ft_lstclear(&root->env, free);
	exit(g_exit_status);
	return (0);
}
