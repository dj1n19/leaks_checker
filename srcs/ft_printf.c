/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:36:21 by bgenie            #+#    #+#             */
/*   Updated: 2022/04/19 16:13:37 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	size_t	count;

	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_parse_format(*str++, ap);
		}
		else
		{
			write(1, str, 1);
			count++;
			str++;
		}
	}
	va_end(ap);
	return (count);
}
