/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:04:25 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/02 15:08:44 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_mode(char *s)
{
	if (s[0] == '>')
	{
		if (s[1] && s[1] == '>')
			return (OUT_APPEND);
		else
			return (OUT_TRUNC);
	}
	else if (s[0] == '<')
	{
		if (s[1] && s[1] == '<')
			return (IN_LIMITER);
		else
			return (IN_FILE);
	}
	return (-1);
}

static int	ft_get_file_cut(char *s)
{
	int	size;
	int	quote;

	size = 0;
	while (*s == '>' || *s == '<')
		s++;
	while (*s == ' ')
		s++;
	quote = 0;
	while (s[size] && (s[size] != ' ' || quote))
		ft_check_quote(s[size++], &quote);
	return (size);
}

char	*ft_get_first_file(char *s)
{
	char	*str;
	int		i;
	int		size;

	size = ft_get_file_cut(s);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (*s == '>' || *s == '<')
		s++;
	while (*s == ' ')
		s++;
	i = 0;
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	ft_get_beginning(char *s)
{
	int	i;
	int	quote;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
		i++;
	while (s[i] == ' ')
		i++;
	quote = 0;
	while (s[i] && (s[i] != ' ' || quote))
		ft_check_quote(s[i++], &quote);
	return (i);
}

char	*ft_get_other_files(char *s)
{
	char	*str;
	int		beg;
	int		i;

	beg = ft_get_beginning(s);
	i = 0;
	while (s[beg + i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[beg + i])
	{
		str[i] = s[beg + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
