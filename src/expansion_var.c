/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:20:31 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/21 15:27:00 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_p(char **split, char *var, t_point *p, int size)
{
	if (split[p->i + ft_size_var(var) - 1][size])
	{
		p->i += ft_size_var(var) - 1;
		p->j = size - 1;
	}
	else
	{
		p->i += ft_size_var(var);
		p->j = -1;
	}
}

static char	**ft_expansion_var_quote(char **split, char *var, t_point *p)
{
	int	size;

	if (var[0] == ' ' && p->j)
	{
		split = ft_new_split_expansion(split, p->i++, p->j);
		if (error_catch(split == NULL, "system", "Malloc failed"))
			return (NULL);
		p->j = 0;
	}
	if (var[ft_strlen(var) - 1] == ' ' && split[p->i][p->j + ft_strlen(var)])
	{
		split = ft_new_split_expansion(split, p->i, p->j + ft_strlen(var));
		if (error_catch(split == NULL, "system", "Malloc failed"))
			return (NULL);
	}
	size = ft_new_split(&split, *p, var, ft_size_var(var));
	if (error_catch(!size, "system", "Malloc failed"))
		return (ft_free_split_char(split));
	ft_change_p(split, var, p, size);
	return (split);
}

char	**ft_expansion_var(char **split, char *var, t_point *p, int quote)
{
	split[p->i] = ft_insert_str(split, split[p->i], var, p->j);
	if (error_catch(split[p->i] == NULL, "system", "Malloc failed"))
		return (NULL);
	if (!quote)
		return (ft_expansion_var_quote(split, var, p));
	p->j += ft_strlen(var) - 1;
	return (split);
}
