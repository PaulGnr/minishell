/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:18:01 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/20 14:38:44 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_process(t_cmd *cmds, int nb_of_cmd)
{
	int	i;
	int	ret;
	int	status;

	status = -1;
	i = 0;
	while (i < nb_of_cmd)
		ret = waitpid(cmds[i++].pid, &status, 0);
	if (status != -1 && g_exit_status != 130 && g_exit_status != 131 && ret > 0)
		g_exit_status = WEXITSTATUS(status);
	return (SUCCESS);
}

int	split_cmd(t_cmd *cmds, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		if (cmds[i].cmd)
		{
			cmds[i].split_cmd = ft_split_quote(cmds[i].cmd, ' ');
			if (error_catch(cmds[i].split_cmd == NULL, "system", "wtf"))
			{
				while (i--)
					free_split(cmds[i].split_cmd);
				return (ERROR);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	free_split_cmd(t_cmd *cmds, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		if (cmds[i].split_cmd)
			free_split(cmds[i].split_cmd);
		i++;
	}
	return (SUCCESS);
}

void	exec_loop(t_cmd *cmds, int nb_of_cmd, t_pipe pipe_fd, t_root *root)
{
	int	(*builtin)(t_cmd *cmd, t_root *root);
	int	i;

	i = 0;
	while (i < nb_of_cmd)
	{
		if (open_fd(cmds[i].redir, root) == SUCCESS && cmds[i].cmd)
		{
			cmds[i].fd_in = select_fd_in(&cmds[i], i, pipe_fd);
			cmds[i].fd_out = select_fd_out(&cmds[i], i, pipe_fd, nb_of_cmd);
			builtin = detect_builtin(&cmds[i]);
			if (builtin)
				exec_builtin(builtin, &cmds[i], root);
			else
				exec_cmd(&cmds[i], root);
		}
		close_fd(cmds[i++].redir);
	}
}

int	exec_all_cmd(t_cmd *cmds, int nb_of_cmd, t_root *root)
{
	if (cmds == NULL)
		return (SUCCESS);
	root->pipe_fd = open_pipe(nb_of_cmd);
	if (root->pipe_fd == NULL)
		return (ERROR);
	if (split_cmd(cmds, nb_of_cmd) == ERROR)
	{
		close_pipe(root->pipe_fd, root->nb_of_cmd);
		return (ERROR);
	}
	if (open_heredoc(cmds, root) == ERROR)
	{
		free_split_cmd(cmds, root->nb_of_cmd);
		close_pipe(root->pipe_fd, root->nb_of_cmd);
		return (ERROR);
	}
	exec_loop(cmds, nb_of_cmd, root->pipe_fd, root);
	close_pipe(root->pipe_fd, root->nb_of_cmd);
	free_split_cmd(cmds, root->nb_of_cmd);
	return (wait_process(cmds, root->nb_of_cmd));
}
