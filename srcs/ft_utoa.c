/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 22:58:03 by bgenie            #+#    #+#             */
/*   Updated: 2022/04/22 16:46:02 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

static int	ft_nbr_size(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_utoa(unsigned int n)
{
	char	*anbr;
	char	*anbr_begin;

	anbr = malloc(ft_nbr_size(n) + 1);
	if (!anbr)
		return (NULL);
	anbr_begin = anbr;
	anbr += ft_nbr_size(n);
	*anbr-- = 0;
	if (n == 0)
		*anbr = 48;
	while (n != 0)
	{
		*anbr-- = n % 10 + 48;
		n /= 10;
	}
	return (anbr_begin);
}
