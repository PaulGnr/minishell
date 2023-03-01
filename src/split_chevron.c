/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:38:39 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/02 16:00:39 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_chevron(char c, char prec)
{
	if ((c == '<' || c == '>') && !prec)
		return (1);
	if ((c == '<' || c == '>') && prec == c)
		return (1);
	return (0);
}

static int	ft_tabsize(char const *s)
{
	int	i;
	int	size;
	int	quote;

	i = 0;
	size = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && ft_is_chevron(s[i], 0))
		{
			size++;
			i++;
			if (ft_is_chevron(s[i], s[i - 1]))
				i++;
		}
		if (i == 0 && !ft_is_chevron(s[i], 0) && s[i] != ' ')
			size++;
		ft_check_quote(s[i], &quote);
		while ((quote || !ft_is_chevron(s[i], 0)) && s[i])
			ft_check_quote(s[i++], &quote);
	}
	return (size);
}

static int	ft_trimed_length(const char *s)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while ((len == 0 && ft_is_chevron(s[len], 0))
		|| (len == 1 && ft_is_chevron(s[len], s[len - 1])))
		len++;
	while ((!ft_is_chevron(s[len], 0) || quote) && s[len])
		ft_check_quote(s[len++], &quote);
	while (len > 1 && s[len - 1] == ' ')
		len--;
	return (len);
}

static int	ft_fillstr(char const *s, char **split)
{
	int	pos;
	int	len;

	pos = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
		{
			len = ft_trimed_length(s);
			split[pos] = (char *)malloc(sizeof(char) * (len + 1));
			if (!split[pos])
				return (ft_free_split(split));
			ft_strlcpy(split[pos], s, len + 1);
			s += len;
			pos++;
		}
	}
	return (1);
}

char	**ft_split_chevron(const char *s)
{
	char	**split;
	int		size;

	if (!s)
		return (NULL);
	size = ft_tabsize(s);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	if (!ft_fillstr(s, split))
		return (NULL);
	split[size] = NULL;
	return (split);
}
