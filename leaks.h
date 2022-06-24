/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:21:01 by bgenie            #+#    #+#             */
/*   Updated: 2022/06/22 16:21:02 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKS_H
# define LEAKS_H
# include <dlfcn.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct vector
{
    void      **ptr;
    size_t    size;
    size_t    max_size;
} vector;

void    *malloc(size_t size);
void    free(void *ptr);
void    check_leaks(void);
void    init_leaks(void);

#endif
