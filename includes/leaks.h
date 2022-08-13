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
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct vector
{
    void        **ptr;
    size_t      size;
    size_t      max_size;
    int         *line;
    char        **file;
    char  **function;
} vector;

void    *ft_malloc(size_t size, int line, char *function, char *file);
void    free(void *ptr);
void    check_leaks(void);

int		ft_printf(const char *str, ...);
size_t	ft_parse_format(char c, va_list ap);
size_t	ft_printchar(int c);
size_t	ft_printstr(char *str);
size_t	ft_printptr(void *ptr);
size_t	ft_printdec(int nbr);
size_t	ft_printudec(unsigned int nbr);
size_t	ft_printhex(char *hex, int upper, int padding);
char	*ft_utohex(unsigned int nbr);
int     ft_toupper(int c);
size_t  ft_strlen(const char *s);
void    ft_putstr_fd(char *s, int fd);
char    *ft_itoa(int n);
char    *ft_utoa(unsigned int n);
void    ft_putchar_fd(char c, int fd);

# define malloc(size) ft_malloc(size, (int)__LINE__, (char *)strdup(__FUNCTION__), (char *)strdup(__FILE__))
#endif
