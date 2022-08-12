/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 23:48:01 by bgenie            #+#    #+#             */
/*   Updated: 2022/05/02 17:02:39 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

size_t	ft_printdec(int nbr)
{
	char	*anbr;
	size_t	size;

	anbr = ft_itoa(nbr);
	if (!anbr)
		return (0);
	ft_putstr_fd(anbr, 1);
	size = ft_strlen(anbr);
	free(anbr);
	return (size);
}
