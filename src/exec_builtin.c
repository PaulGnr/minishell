/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:14:05 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/20 15:55:52 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_close(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

t_builtin	detect_builtin(t_cmd *cmd)
{
	const char	*builtin_name[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	static int	(*builtin[7])(t_cmd *cmd, t_root *root) = {ft_echo, ft_cd,
		ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	int			i;

	i = 0;
	while (builtin_name[i])
	{
		if (ft_strncmp(cmd->split_cmd[0], builtin_name[i],
				ft_strlen(builtin_name[i]) + 1) == 0)
			return (builtin[i]);
		i++;
	}
	return (NULL);
}

int	exec_builtin(int (*builtin)(t_cmd *, t_root *), t_cmd *cmd, t_root *root)
{
	int	signal;

	cmd->split_cmd = ft_expansion(cmd->split_cmd, root->env);
	if (root->nb_of_cmd == 1)
		g_exit_status = builtin(cmd, root);
	else
	{
		cmd->pid = fork();
		error_catch(cmd->pid == -1, "system", "fail to create fork");
		if (cmd->pid == 0)
		{
			sig_handling_child_proc();
			signal = builtin(cmd, root);
			close_fd(cmd->redir);
			close_pipe(root->pipe_fd, root->nb_of_cmd);
			ft_lstclear(&root->env, free);
			free_split_cmd(root->cmds, root->nb_of_cmd);
			free_and_close(cmd);
			ft_free_cmds(root->cmds, root);
			exit(signal);
		}
	}
	return (SUCCESS);
}
