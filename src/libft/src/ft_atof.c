/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaubert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:31:58 by sgaubert          #+#    #+#             */
/*   Updated: 2021/10/08 15:32:00 by sgaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(const char *nptr)
{
	int		i;
	int		j;
	float	nb;
	int		signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			signe = -signe;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + nptr[i++] - 48;
	if (nptr[i] == '.')
		i++;
	j = 10;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb += (float)(nptr[i++] - 48) / j;
		j *= 10;
	}
	return (nb * signe);
}
