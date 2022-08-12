/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:44:05 by bgenie            #+#    #+#             */
/*   Updated: 2022/05/03 13:47:30 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

static size_t	ft_print32b(unsigned long int addr)
{
	size_t			size;
	char			*hex;
	unsigned int	word;

	size = 0;
	if (addr > 4294967295)
	{
		word = (unsigned int)(addr >> 32);
		hex = ft_utohex(word);
		if (!hex)
			return (0);
		size += ft_printhex(hex, 0, 0);
	}
	word = (unsigned int) addr;
	hex = ft_utohex(word);
	if (!hex)
		return (0);
	if (addr > 4294967295)
		size += ft_printhex(hex, 0, 8 - ft_strlen(hex));
	else
		size += ft_printhex(hex, 0, 0);
	return (size);
}

size_t	ft_printptr(void *ptr)
{
	unsigned long int	addr;
	size_t				size;

	size = 0;
	addr = (unsigned long int) ptr;
	write(1, "0x", 2);
	size = ft_print32b(addr);
	return (size + 2);
}
