/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:32:51 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/22 08:32:54 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*c_dest;
	char	*c_src;

	c_dest = (char *)dest;
	c_src = (char *)src;
	if (c_src < c_dest)
	{
		i = n - 1;
		j = 0;
		while (j++ < n)
		{
			c_dest[i] = c_src[i];
			i--;
		}
	}
	else if (c_src > c_dest)
	{
		i = -1;
		while (++i < n)
			c_dest[i] = c_src[i];
	}
	return (dest);
}
