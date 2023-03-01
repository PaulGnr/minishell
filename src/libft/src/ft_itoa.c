/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 08:41:41 by sgaubert          #+#    #+#             */
/*   Updated: 2021/05/22 08:41:43 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	nb;
	char	*dst;
	int		i;

	nb = (long)n;
	i = 0;
	if (n <= 0)
		i++;
	while (n && i++ != -1)
		n /= 10;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i--] = 0;
	if (nb < 0)
		nb = -nb;
	dst[0] = '-';
	if (nb == 0)
		dst[0] = '0';
	while (nb)
	{
		dst[i--] = nb % 10 + 48;
		nb /= 10;
	}
	return (dst);
}
