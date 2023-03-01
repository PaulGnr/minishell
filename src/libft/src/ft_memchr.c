/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:33:05 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/22 08:33:10 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	i = -1;
	while (++i < n)
		if (*c_s++ == (unsigned char)c)
			return ((unsigned char *)s + i);
	return (NULL);
}
