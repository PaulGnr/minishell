/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:15:34 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/25 18:04:05 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quote(char c, int *quote)
{
	if (c == '\'' && !(*quote))
		*quote = 1;
	else if (c == '\"' && !(*quote))
		*quote = 2;
	else if ((c == '\'' && *quote == 1) || (c == '\"' && *quote == 2))
		*quote = 0;
}

int	error_pipe(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
	return (0);
}

int	error_syntax(void)
{
	g_exit_status = 1;
	return (0);
}

int	ft_check_chevron(char *str, int i, int *quote, int *chevron)
{
	ft_check_quote(str[i], quote);
	if (!(*quote))
	{
		if (!(*chevron) && str[i] == '|')
			*chevron = 5;
		else if (!(*chevron) && str[i] == '>')
			*chevron = 1;
		else if (!(*chevron) && str[i] == '<')
			*chevron = 2;
		else if (*chevron == 1 && str[i] == '>' && str[i - 1] == '>')
			*chevron = 3;
		else if (*chevron == 2 && str[i] == '<' && str[i - 1] == '<')
			*chevron = 4;
		else if (*chevron && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			return (0);
		else if (*chevron && str[i] != ' ')
			*chevron = 0;
	}
	return (1);
}

int	ft_check_str(char *str)
{
	int	i;
	int	quote;
	int	chevron;

	i = 0;
	quote = 0;
	chevron = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (error_pipe('|'));
	while (str[i])
	{
		if (!ft_check_chevron(str, i++, &quote, &chevron))
			return (error_pipe(str[i - 1]));
	}
	if (error_catch(quote, "syntax", "Syntax error"))
		return (error_syntax());
	if (i)
		i--;
	while (str[i] == ' ' && i > 0)
		i--;
	if (error_catch(str[i] == '|', "syntax", "Syntax error"))
		return (error_syntax());
	return (1);
}
