/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:52:05 by bgenie            #+#    #+#             */
/*   Updated: 2022/04/22 16:49:24 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

char	*ft_utohex(unsigned int nbr)
{
	char	*hex;
	int		i;

	i = 0;
	hex = malloc(sizeof(char) * 9);
	if (!hex)
		return (NULL);
	if (nbr == 0)
		hex[i++] = 48;
	while (nbr != 0)
	{
		if (nbr % 16 > 9)
			hex[i++] = nbr % 16 + 87;
		else
			hex[i++] = nbr % 16 + 48;
		nbr /= 16;
	}
	hex[i] = 0;
	return (hex);
}
