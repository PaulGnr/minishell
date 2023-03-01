/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:19:20 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/25 18:10:15 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_dir(char *cmd, char **cmd_path, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*str;

	dir = opendir(path);
	if (dir == NULL)
		return (ERROR);
	dirent = readdir(dir);
	while (dirent && ft_strncmp(cmd, "..", 3) != 0)
	{
		if (ft_strncmp(cmd, dirent->d_name, ft_strlen(cmd) + 1) == 0)
		{
			str = ft_strjoin(path, "/");
			if (error_catch(str == NULL, "system", NULL))
				return (ERROR);
			*cmd_path = ft_strjoin(str, cmd);
			free(str);
			closedir(dir);
			return (SUCCESS);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (FAIL);
}

static int	open_file(char *cmd, char **cmd_path)
{
	int				fd;
	DIR				*dir;

	dir = opendir(cmd);
	if (error_catch(dir != NULL, cmd, "Is a directory"))
	{
		g_exit_status = 126;
		closedir(dir);
		return (FAIL);
	}
	fd = open(cmd, O_RDONLY);
	if (error_catch(fd < 0, cmd, NULL))
	{
		g_exit_status = 127;
		return (FAIL);
	}
	close(fd);
	*cmd_path = ft_strdup(cmd);
	if (*cmd_path == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	get_cmd_path(char *cmd, char **cmd_path, t_root *root)
{
	char	**path;
	char	*env_path;
	int		i;
	int		retvar;

	env_path = get_env("PATH", root->env);
	if (error_catch(!env_path || ft_strlen(env_path) == 0,
			cmd, "No such file or directory"))
	{
		g_exit_status = 127;
		return (FAIL);
	}
	path = ft_split(env_path, ':');
	if (error_catch(path == NULL, "system", NULL))
		return (ERROR);
	i = 0;
	while (path[i])
	{
		retvar = read_dir(cmd, cmd_path, path[i++]);
		if (retvar == SUCCESS)
			return (!ft_free_split(path));
	}
	error_catch(1, cmd, "command not found");
	g_exit_status = 127;
	return (ft_free_split(path));
}

t_bool	find_cmd(char *cmd, char **cmd_path, t_root *root)
{
	int	is_find;

	if (!cmd)
	{
		g_exit_status = 0;
		return (SUCCESS);
	}
	if (error_catch(ft_strncmp(cmd, ".", 2) == 0, cmd,
			"filename argument required"))
	{
		g_exit_status = 2;
		return (1);
	}
	*cmd_path = NULL;
	if (ft_strchr(cmd, '/'))
		is_find = open_file(cmd, cmd_path);
	else
		is_find = get_cmd_path(cmd, cmd_path, root);
	if (is_find == ERROR)
		g_exit_status = 1;
	else if (is_find == SUCCESS)
		g_exit_status = 0;
	return (is_find == ERROR || is_find == FAIL);
}
