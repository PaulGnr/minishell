/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:32:13 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/08 15:32:16 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_gnl(int fd, char **line)
{
	char		buffer[1024][2];
	int			ret;
	char		*tmp;

	if (read(fd, buffer[0], 0) == -1 || !line)
		return (-1);
	*line = ft_strdup("");
	buffer[fd][1] = 0;
	while (1)
	{
		ret = read(fd, buffer[fd], 1);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (0);
		if (buffer[fd][0] == '\n')
			return (1);
		tmp = ft_strjoin(*line, buffer[fd]);
		free(*line);
		*line = tmp;
	}
	return (1);
}
