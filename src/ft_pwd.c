/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:44:30 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/18 17:33:03 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	*buf;
	int		i;

	i = 1;
	errno = 1;
	while (errno)
	{
		errno = 0;
		buf = (char *)malloc(sizeof(char) * i);
		if (error_catch(buf == NULL, "system", "Malloc failed"))
			return (NULL);
		getcwd(buf, i++);
		if (!errno)
			return (buf);
		else
			free(buf);
	}
	return (buf);
}

int	ft_is_multi_slash(t_root *root, char *pwd)
{
	t_list	*env;

	env = root->env;
	while (env && ft_strncmp((char *)env->content, "PWD=", 4))
		env = env->next;
	if (!env)
		return (0);
	if (!ft_strncmp(&(((char *)env->content)[4]), "//", 2)
		&& !ft_strncmp(&(((char *)env->content)[5]), pwd, ft_strlen(pwd) + 1))
		return (1);
	return (0);
}

int	ft_pwd(t_cmd *cmd, t_root *root)
{
	char	*buf;
	int		i;

	(void)root;
	i = 1;
	errno = 0;
	buf = (char *)malloc(sizeof(char) * i);
	if (!buf)
		exit(error_catch(1, "system", "Malloc failed"));
	getcwd(buf, i++);
	while (errno)
	{
		errno = 0;
		free(buf);
		buf = (char *)malloc(sizeof(char) * i);
		if (!buf)
			exit(error_catch(1, "system", "Malloc failed"));
		getcwd(buf, i++);
	}
	if (ft_is_multi_slash(root, buf))
		ft_putstr_fd("/", cmd->fd_out);
	ft_putstr_fd(buf, cmd->fd_out);
	ft_putstr_fd("\n", cmd->fd_out);
	free(buf);
	return (0);
}
