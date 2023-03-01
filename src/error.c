/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:19:25 by sgaubert          #+#    #+#             */
/*   Updated: 2021/09/09 15:19:27 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	error_catch(t_bool test, char *str, char *error_msg)
{
	const int	error = errno;

	if (test && error != 8)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		if (error_msg == NULL)
			ft_putstr_fd(strerror(error), 2);
		else
			ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (test);
}

t_bool	not_a_valid_identifier(t_bool test, char *fct_name, char *identifier)
{
	if (test)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(fct_name, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(identifier, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (test);
}
