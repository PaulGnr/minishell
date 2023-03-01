/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:43:04 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/21 14:43:21 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **start, t_list *new)
{
	t_list	*copy_start;

	copy_start = *start;
	if (!*start)
		*start = new;
	else
	{
		while (copy_start->next)
			copy_start = copy_start->next;
		copy_start->next = new;
	}
}
