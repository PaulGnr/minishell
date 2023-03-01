/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:31:32 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/08 15:31:34 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_front(t_list **lst)
{
	t_list	*node;

	node = *lst;
	*lst = (*lst)->next;
	node->next = NULL;
	return (node);
}
