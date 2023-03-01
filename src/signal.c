/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:29:25 by sgaubert          #+#    #+#             */
/*   Updated: 2023/03/01 17:11:43 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_exit_status > -1)
		{
			rl_on_new_line();
#ifdef Linux
			rl_replace_line("", 0);
#endif
			rl_redisplay();
		}
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		if (g_exit_status == -1)
			g_exit_status = 131;
	}
}

static void	sig_handler_heredoc(int signum)
{
	if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "  ", 2);
	}
}

int	sig_handling_parent_proc(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}

int	sig_handling_child_proc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (0);
}

int	sig_handling_heredoc_proc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_handler_heredoc);
	return (0);
}
