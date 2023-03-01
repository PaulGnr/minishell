/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:19:14 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/14 17:23:02 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_last_fd_in_or_out(t_redir *redir, int test_one, int test_two)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (redir->mode == test_one || redir->mode == test_two)
			fd = redir->fd;
		redir = redir->next;
	}
	return (fd);
}

int	select_fd_in(t_cmd *cmd, int cmd_index, int (*pipe_fd)[2])
{
	int	fd;

	fd = find_last_fd_in_or_out(cmd->redir, IN_FILE, IN_LIMITER);
	if (fd == -1)
	{
		if (cmd_index == 0)
			fd = 0;
		else
			fd = pipe_fd[cmd_index - 1][0];
	}
	return (fd);
}

int	select_fd_out(t_cmd *cmd, int cmd_index, int (*pipe_fd)[2], int nb_of_cmd)
{
	int	fd;

	fd = find_last_fd_in_or_out(cmd->redir, OUT_TRUNC, OUT_APPEND);
	if (fd == -1)
	{
		if (cmd_index == nb_of_cmd - 1)
			fd = 1;
		else
			fd = pipe_fd[cmd_index][1];
	}
	return (fd);
}
