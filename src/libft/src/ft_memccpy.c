/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:32:15 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/22 08:32:30 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;

	c_dest = (char *)dest;
	c_src = (char *)src;
	i = 0;
	while (i < n && (unsigned char)c_src[i] != (unsigned char)c)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	if (i == n)
		return (NULL);
	if ((unsigned char)c_src[i] == (unsigned char)c)
	{
		c_dest[i] = (unsigned char)c_src[i];
		return (dest + i + 1);
	}
	return (NULL);
}
