/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:21:01 by bgenie            #+#    #+#             */
/*   Updated: 2023/03/30 21:00:34 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKS_H
# define LEAKS_H
# include <dlfcn.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_vector
{
    void        **ptr;
    size_t      size;
    size_t      max_size;
	size_t		*msize;
    int         *line;
    char        **file;
    char  		**function;
} vector;

void    *ft_malloc(size_t size, int line, char *function, char *file);
void    ft_free(void *ptr);
void    check_leaks(void);

# define free(ptr) ft_free(ptr)
# define malloc(size) ft_malloc(size, (int)__LINE__, (char *)strdup(__FUNCTION__), (char *)strdup(__FILE__))
#endif
