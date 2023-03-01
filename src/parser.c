/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:37:26 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/19 18:16:23 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*ft_cmdlast(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir->next)
		redir = redir->next;
	return (redir);
}

static int	ft_multiple_files(char *s)
{
	int	i;
	int	quote;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
		i++;
	while (s[i] == ' ')
		i++;
	quote = 0;
	while (s[i])
	{
		ft_check_quote(s[i], &quote);
		if (s[i] == ' ' && !quote)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_fill_cmds_two(t_cmd *cmds, char **split_two, int i)
{
	t_redir	*redir;

	while (split_two[i])
	{
		redir = (t_redir *)malloc(sizeof(t_redir));
		if (!redir)
			return (0);
		redir->next = NULL;
		if (!cmds->redir)
			cmds->redir = redir;
		else
			ft_cmdlast(cmds)->next = redir;
		redir->mode = ft_get_mode(split_two[i]);
		redir->str = ft_get_first_file(split_two[i]);
		if (ft_multiple_files(split_two[i]))
		{
			cmds->cmd = ft_strjoin_malloc(cmds->cmd,
					ft_get_other_files(split_two[i]));
			if (!cmds->cmd)
				return (0);
		}
		i++;
	}
	ft_free_split(split_two);
	return (1);
}

static int	ft_fill_cmds(t_cmd *cmds, char *split)
{
	char	**split_two;
	int		i;

	split_two = ft_split_chevron(split);
	if (!split_two)
		return (0);
	cmds->redir = NULL;
	i = 0;
	if (split_two[0] && split_two[0][0] != '>' && split_two[0][0] != '<')
	{
		cmds->cmd = ft_strdup(split_two[0]);
		if (!cmds->cmd)
			return (ft_free_split(split_two));
		i = 1;
	}
	else
		cmds->cmd = NULL;
	if (!ft_fill_cmds_two(cmds, split_two, i))
	{
		free(cmds->cmd);
		return (ft_free_split(split_two));
	}
	return (1);
}

t_cmd	*ft_parser(char *str, t_root *root)
{
	char	**split_one;
	t_cmd	*cmds;
	int		i;

	split_one = ft_split_quote(str, '|');
	if (!split_one)
		return (NULL);
	cmds = (t_cmd *)malloc(sizeof(t_cmd) * split_size(split_one));
	if (!cmds)
		return (ft_free_split_cmd(split_one));
	root->nb_of_cmd = split_size(split_one);
	i = 0;
	while (split_one[i])
	{
		cmds[i] = init_cmd();
		if (!ft_fill_cmds(&(cmds[i]), split_one[i]))
		{
			ft_free_split(split_one);
			ft_free_cmds(cmds, root);
			return (NULL);
		}
		i++;
	}
	ft_free_split(split_one);
	return (cmds);
}
