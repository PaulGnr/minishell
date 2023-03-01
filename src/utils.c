/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:28:16 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/15 18:39:08 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.cmd = NULL;
	cmd.split_cmd = NULL;
	cmd.pid = -1;
	cmd.fd_in = 0;
	cmd.fd_out = 0;
	cmd.redir = NULL;
	return (cmd);
}

void	ft_free_cmds(t_cmd *cmds, t_root *root)
{
	int		i;
	t_redir	*redir;
	t_redir	*tmp;

	i = 0;
	while (i < root->nb_of_cmd)
	{
		if (cmds[i].cmd)
			free(cmds[i].cmd);
		if (cmds[i].redir)
		{
			redir = cmds[i].redir;
			while (redir)
			{
				free(redir->str);
				tmp = redir;
				redir = redir->next;
				free(tmp);
			}
		}
		i++;
	}
	free(cmds);
}

int	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}

char	**ft_free_split_char(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

t_cmd	*ft_free_split_cmd(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}
