/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:36:14 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/21 18:31:20 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_fork(char *limiter, int heredoc_pipe[2], t_root *root)
{
	char	*line;

	sig_handling_heredoc_proc();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			close_pipe(root->pipe_fd, root->nb_of_cmd);
			ft_lstclear(&root->env, free);
			free_split_cmd(root->cmds, root->nb_of_cmd);
			ft_free_cmds(root->cmds, root);
			free(line);
			exit(0);
		}
		line = ft_expansion_heredoc(line, root->env);
		ft_putstr_fd(line, heredoc_pipe[1]);
		ft_putstr_fd("\n", heredoc_pipe[1]);
		free(line);
	}
}

int	read_heredoc_pipe(char *limiter, t_root *root)
{
	int		heredoc_pipe[2];
	int		pid;
	int		status;

	if (error_catch(pipe(heredoc_pipe) == -1, "system", "fail to open pipe"))
		return (-1);
	pid = fork();
	error_catch(pid == -1, "system", "fail to create fork");
	if (pid == 0)
		in_fork(limiter, heredoc_pipe, root);
	g_exit_status = -2;
	waitpid(pid, &status, 0);
	close(heredoc_pipe[1]);
	if (status == 2)
	{
		close(heredoc_pipe[0]);
		return (-1);
	}
	return (heredoc_pipe[0]);
}

int	close_heredoc(t_cmd *cmds, t_root *root)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < root->nb_of_cmd)
	{
		redir = cmds[i].redir;
		while (redir)
		{
			if (redir->mode == IN_LIMITER)
			{
				if (redir->fd == -1)
					return (ERROR);
				close(redir->fd);
			}
			redir = redir->next;
		}
		i++;
	}
	return (SUCCESS);
}

int	open_heredoc(t_cmd *cmds, t_root *root)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < root->nb_of_cmd)
	{
		redir = cmds[i].redir;
		while (redir)
		{
			if (redir->mode == IN_LIMITER)
			{
				redir->str = ft_get_limiter(redir->str);
				redir->fd = read_heredoc_pipe(redir->str, root);
				if (redir->fd == -1)
				{
					close_heredoc(cmds, root);
					return (ERROR);
				}
			}
			redir = redir->next;
		}
		i++;
	}
	return (SUCCESS);
}
