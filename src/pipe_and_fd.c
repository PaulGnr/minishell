/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:19:04 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/25 18:00:13 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_str(t_redir *redir, t_root *root)
{
	char	*save_str;

	save_str = ft_strdup(redir->str);
	if (error_catch(save_str == NULL, "system", "Malloc fail"))
		return (ERROR);
	redir->str = expansion_redir(redir->str, root->env);
	if (!redir->str)
		return (ERROR);
	if (redir->str[0] == 0)
	{
		if (save_str[0] != '\"' && save_str[0] != '\'')
		{
			redir->fd = -2;
			free(redir->str);
			redir->str = save_str;
		}
		if (save_str[0] == '\"' || save_str[0] == '\'')
			redir->fd = -1;
		return (FAIL);
	}
	free(save_str);
	return (SUCCESS);
}

int	open_fd(t_redir *redir, t_root *root)
{
	while (redir)
	{
		if (redir->mode != IN_LIMITER && expand_str(redir, root) == SUCCESS)
		{
			if (redir->mode == OUT_TRUNC || redir->mode == OUT_APPEND)
			{
				redir->fd = open(redir->str, O_WRONLY | redir->mode);
				if (redir->fd == -1)
					redir->fd = open(redir->str, O_WRONLY | O_CREAT, 0664);
			}
			else if (redir->mode == IN_FILE)
				redir->fd = open(redir->str, O_RDONLY);
		}
		if (error_catch(redir->fd == -1, redir->str,
				"No such file or directory")
			|| error_catch(redir->fd == -2, redir->str,
				"ambiguous redirect"))
		{
			g_exit_status = 1;
			return (FAIL);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}

void	close_fd(t_redir *redir)
{
	while (redir)
	{
		if (redir->fd < 0)
			return ;
		close(redir->fd);
		redir = redir->next;
	}
}

t_pipe	open_pipe(int nb_of_cmd)
{
	int		i;
	t_pipe	pipe_fd;

	pipe_fd = malloc(sizeof(int [2]) * (nb_of_cmd - 1));
	if (error_catch(pipe_fd == 0, "system", "fail to malloc pipe table"))
		return (NULL);
	i = 0;
	while (i < nb_of_cmd - 1)
	{
		if (error_catch(pipe(pipe_fd[i++]) == -1, "system",
				"fail to open pipe"))
		{
			while (--i)
			{
				close(pipe_fd[i][0]);
				close(pipe_fd[i][1]);
			}
			free(pipe_fd);
			return (NULL);
		}
	}
	return (pipe_fd);
}

void	close_pipe(int (*pipe_fd)[2], int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i++][1]);
	}
	free(pipe_fd);
}
