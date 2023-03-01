/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:06:15 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 18:12:07 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	ft_error_str(char *str, t_root root)
{
	ft_putstr_fd("exit\n", 1);
	free(str);
	free(root.shell_env);
	ft_lstclear(&root.env, free);
	return (0);
}

int	exec_minishell(char *str, t_root root, t_cmd *cmds)
{
	cmds = ft_parser(str, &root);
	if (!cmds)
		return (ft_error_str(str, root));
	free(str);
	root.cmds = cmds;
	exec_all_cmd(cmds, root.nb_of_cmd, &root);
	ft_free_cmds(cmds, &root);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_root	root;
	t_cmd	*cmds;

	(void)argv;
	cmds = NULL;
	if (argc == 1)
	{
		sig_handling_parent_proc();
		if (create_env(envp, &root) == ERROR)
			return (1);
		while (1)
		{
			str = readline("\033[1;35mminishell> \033[0m");
			if (!str)
				return (ft_error_str(str, root));
			add_history(str);
			if (!ft_check_str(str))
				free(str);
			else if (str[0])
				if (!exec_minishell(str, root, cmds))
					return (1);
		}
	}
	return (0);
}
