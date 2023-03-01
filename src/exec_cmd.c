/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:18:50 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/20 14:39:46 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_close(t_cmd *cmd, char *cmd_path)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	free(cmd_path);
}

char	**ft_get_lstenv(t_list *env)
{
	char	**split;
	int		i;

	split = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (env)
	{
		split[i] = ft_strdup((char *)env->content);
		if (!split[i++])
		{
			ft_free_split(split);
			return (NULL);
		}
		env = env->next;
	}
	split[i] = NULL;
	return (split);
}

static void	close_useless_pipe(t_cmd *cmd, t_root *root)
{
	int		i;

	i = -1;
	while (++i < root->nb_of_cmd - 1)
	{
		if (root->pipe_fd[i][0] != cmd->fd_in
			&& root->pipe_fd[i][0] != cmd->fd_out)
			close(root->pipe_fd[i][0]);
		if (root->pipe_fd[i][1] != cmd->fd_out
			&& root->pipe_fd[i][1] != cmd->fd_in)
			close(root->pipe_fd[i][1]);
	}
}

static void	in_fork(t_cmd *cmd, char *cmd_path, t_root *root)
{
	sig_handling_child_proc();
	close_useless_pipe(cmd, root);
	if (error_catch(dup2(cmd->fd_in, 0) == -1, "dup2 in", NULL))
		exit(1);
	if (error_catch(dup2(cmd->fd_out, 1) == -1, "dup2 out", NULL))
		exit(1);
	root->shell_env = ft_get_lstenv(root->env);
	if (error_catch(root->shell_env == NULL, "system", "Malloc failed"))
		exit(1);
	execve(cmd_path, cmd->split_cmd, root->shell_env);
	error_catch(1, cmd->split_cmd[0], NULL);
	close_fd(cmd->redir);
	close_pipe(root->pipe_fd, root->nb_of_cmd);
	ft_lstclear(&root->env, free);
	ft_free_split(root->shell_env);
	free_split_cmd(root->cmds, root->nb_of_cmd);
	free_and_close(cmd, cmd_path);
	ft_free_cmds(cmd, root);
	exit(126);
}

int	exec_cmd(t_cmd *cmd, t_root *root)
{
	char	*cmd_path;

	cmd->split_cmd = ft_expansion(cmd->split_cmd, root->env);
	if (!cmd->split_cmd)
		return (ERROR);
	if (find_cmd(cmd->split_cmd[0], &cmd_path, root))
		return (ERROR);
	cmd->pid = fork();
	error_catch(cmd->pid == -1, "system", NULL);
	if (cmd->pid == 0)
		in_fork(cmd, cmd_path, root);
	g_exit_status = -1;
	free_and_close(cmd, cmd_path);
	return (SUCCESS);
}
