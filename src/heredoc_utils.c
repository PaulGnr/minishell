/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:26:50 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 18:33:57 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove_quote_str(char *str, int pos, int size)
{
	char	*cpy;

	if (!str)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, str, pos + 1);
	ft_strlcat(cpy, &(str[pos + size]), ft_strlen(str) - size + 1);
	free(str);
	return (cpy);
}

char	*ft_get_limiter(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		ft_check_quote(str[i], &quote);
		if ((str[i] == '\'' && quote != 2)
			|| (str[i] == '\"' && quote != 1))
		{
			str = ft_remove_quote_str(str, i--, 1);
			if (error_catch(!str, "here_doc", "Malloc failed"))
				return (NULL);
		}
		i++;
	}
	return (str);
}
