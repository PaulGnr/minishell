/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:37:39 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/01 16:50:24 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	temp = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	while (dest[i])
		i++;
	while (src[j] != '\0' && i < size - 1)
		dest[i++] = src[j++];
	dest[i] = 0;
	if (size < temp)
		return (size + ft_strlen(src));
	else
		return (temp + ft_strlen(src));
}
