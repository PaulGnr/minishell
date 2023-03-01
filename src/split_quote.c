/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:38:39 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/02 15:59:26 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tabsize(char const *s, char c)
{
	int	i;
	int	size;
	int	quote;

	i = 0;
	size = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && ((i == 0 && s[i] != c) || (i != 0
					&& s[i - 1] == c && s[i] != c)))
			size++;
		ft_check_quote(s[i], &quote);
		i++;
	}
	return (size);
}

static int	ft_trimed_length(const char *s, int c)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while (s[len] && (s[len] != c || quote))
	{
		ft_check_quote(s[len], &quote);
		len++;
	}
	while (len > 1 && s[len - 1] == ' ')
		len--;
	return (len);
}

static int	ft_fillstr(char const *s, char c, char **split)
{
	int	pos;
	int	len;

	pos = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			while (*s == ' ')
				s++;
			len = ft_trimed_length(s, c);
			split[pos] = (char *)malloc(sizeof(char) * (len + 1));
			if (!split[pos])
				return (ft_free_split(split));
			ft_strlcpy(split[pos], s, len + 1);
			s += len;
			while (*s == ' ')
				s++;
			pos++;
		}
	}
	return (1);
}

char	**ft_split_quote(const char *s, char c)
{
	char	**split;
	int		size;

	if (!s)
		return (NULL);
	size = ft_tabsize(s, c);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	if (!ft_fillstr(s, c, split))
		return (NULL);
	split[size] = NULL;
	return (split);
}
