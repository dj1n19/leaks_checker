/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:58:02 by bgenie            #+#    #+#             */
/*   Updated: 2022/08/04 17:30:03 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/leaks.h"

static vector	v_malloc;

static vector *v_resize(vector *v, size_t new_size) {
    void **new;

    if (new_size < v->size)
    {
        dprintf(2, "\e[31mLEAKS.ERROR: new size smaller than current size\n\e[0m\n");
        exit(EXIT_FAILURE);
    }
    new = (void **) realloc(v->ptr, sizeof(void *) * new_size);
    if (!new)
    {
        dprintf(2, "\e[31mLEAKS.ERROR: realloc failed\e[0m\n");
        exit(EXIT_FAILURE);
    }
    v->ptr = new;
    v->max_size = new_size;
    return (v);
}

static vector *v_add(vector *v, void *p, int line, const char *function, char *file) {
    if (v->size >= v->max_size)
        v = v_resize(v, v->max_size + 1);
    v->ptr[v->size] = p;
    v->size++;
    v->line = line;
    v->file = file;
    v->function = function;
    return (v);
}

static vector *v_remove(vector *v, void *p) {
    size_t i = 0;

    for (size_t j = 0; j < v->size && v->ptr[j] != p; ++j)
        i++;
    for (size_t j = i; j + 1 < v->size; ++j)
        v->ptr[j] = v->ptr[j + 1];
    v->size--;
    return (v);
}

static vector *v_clear(vector *v) {
    void *(*libc_free)(void *ptr) = (void *(*)(void *)) dlsym(RTLD_NEXT, "free");
    for (size_t i = 0; i < v->size; ++i)
        libc_free(v->ptr[i]);
    v->size = 0;
    return (v);
}

static void v_puts(vector *v) {
    ft_printf("\e[33m\t===== LEAKS CHECKER =====\e[0m\n");
    for (size_t i = 0; i < v->size; ++i)
    {
        ft_printf("\e[31m[%p]: <%s> in \"%s\":%d\e[0m\n", v->ptr[i], v->function, v->file, v->line);
    }
    ft_printf("\e[33m\t===== %d LEAKS FOUND ! =====\e[0m\n", v->size);
}

void *ft_malloc(size_t size, int line, const char *function, char *file) {

    void *(*libc_malloc)(size_t size) = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");
    void *p = libc_malloc(size);
    if (!p)
        return (NULL);
    v_add(&v_malloc, p, line, function, file);
    return (p);
}

void free(void *ptr) {
    void *(*libc_free)(void *ptr) = (void *(*)(void *)) dlsym(RTLD_NEXT, "free");
	if (ptr)
    	v_remove(&v_malloc, ptr);
    libc_free(ptr);
}

void check_leaks(void) {
    if (v_malloc.size != 0)
    {
        v_puts(&v_malloc);
    }
    else
    {
        ft_printf("\e[32m\t===== NO LEAKS =====\n\e[0m");
    }
    v_clear(&v_malloc);
}
