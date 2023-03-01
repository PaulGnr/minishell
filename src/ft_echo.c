/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:42:54 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/02 16:10:32 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_all_n(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, t_root *root)
{
	int		i;
	t_bool	newline;

	(void)root;
	i = 1;
	newline = 1;
	while (cmd->split_cmd[i] && ft_strncmp(cmd->split_cmd[i], "-n", 2) == 0
		&& ft_is_all_n(cmd->split_cmd[i]))
	{
		i++;
		newline = 0;
	}
	while (cmd->split_cmd[i])
	{
		ft_putstr_fd(cmd->split_cmd[i], cmd->fd_out);
		if (cmd->split_cmd[i + 1])
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
