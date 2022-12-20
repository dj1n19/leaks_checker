/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dj1n <dj1n@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:58:02 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/20 22:31:49 by dj1n             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks.h"

static vector	*v_malloc;

__attribute__((constructor))
void	init(void)
{
	void *(*libc_malloc)(size_t size) = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");
	v_malloc = libc_malloc(sizeof(vector));
	if (!v_malloc)
	{
		dprintf(2, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	v_malloc->size = 0;
	v_malloc->max_size = 8;
	v_malloc->ptr = libc_malloc(sizeof(void *) * 8);
	v_malloc->msize = libc_malloc(sizeof(size_t) * 8);
	v_malloc->line = libc_malloc(sizeof(int) * 8);
	v_malloc->file = libc_malloc(sizeof(char *) * 8);
	v_malloc->function = libc_malloc(sizeof(char *) * 8);
	if (!v_malloc->ptr || !v_malloc->msize || !v_malloc->line || !v_malloc->file || !v_malloc->function)
	{
		dprintf(2, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}
}

__attribute__((destructor))
void	destroy(void)
{
	void *(*libc_free)(void *ptr) = (void *(*)(void *)) dlsym(RTLD_NEXT, "free");
	libc_free(v_malloc->ptr);
	libc_free(v_malloc->msize);
	libc_free(v_malloc->line);
	libc_free(v_malloc->file);
	libc_free(v_malloc->function);
	libc_free(v_malloc);
}

static vector *v_resize(vector *v, size_t new_size) {
    if (new_size < v->size)
    {
        dprintf(2, "\e[31mLEAKS.ERROR: new size smaller than current size\n\e[0m\n");
        exit(EXIT_FAILURE);
    }
    v->ptr = (void **) realloc(v->ptr, sizeof(void *) * new_size);
	v->msize = (size_t *) realloc(v->ptr, sizeof(size_t) * new_size);
    v->line = (int *) realloc(v->line, sizeof(int) * new_size);
    v->file = (char **) realloc(v->file, sizeof(char *) * new_size);
    v->function = (char **) realloc(v->function, sizeof(char *) * new_size); 
    if (!v->ptr || !v->line || !v->file || !v->function)
    {
        dprintf(2, "\e[31mLEAKS.ERROR: realloc failed\e[0m\n");
        exit(EXIT_FAILURE);
    }
    v->max_size = new_size;
    return (v);
}

static vector *v_add(vector *v, void *p, int line, char *function, char *file, size_t msize) {
    if (v->size >= v->max_size)
        v = v_resize(v, v->max_size + 1);
    v->ptr[v->size] = p;
	v->msize[v->size] = msize;
    v->line[v->size] = line;
    v->file[v->size] = file;
    v->function[v->size] = function;
    v->size++;
    return (v);
}

static vector *v_remove(vector *v, void *p) {
    size_t i = 0;

    for (size_t j = 0; j < v->size && v->ptr[j] != p; ++j)
        i++;
    for (size_t j = i; j + 1 < v->size; ++j)
	{
        v->ptr[j] = v->ptr[j + 1];
		v->msize[j] = v->msize[j + 1];
        v->line[j] = v->line[j + 1];
        v->function[j] = v->function[j + 1];
        v->file[j] = v->file[j + 1];
	}
	v->size--;
    return (v);
}

static vector *v_clear(vector *v) {
    for (size_t i = 0; i < v->size; ++i)
        ft_free(v->ptr[i]);
    v->size = 0;
    return (v);
}

static void v_puts(vector *v) {
    printf("\e[33m\t===== LEAKS CHECKER =====\e[0m\n");
    for (size_t i = 0; i < v->size; ++i)
        printf("\e[31m[%p]: <%s> in \"%s\":%d (%lu bytes) \e[0m\n", v->ptr[i], v->function[i], v->file[i], v->line[i], v->msize[i]);
    printf("\e[33m\t===== %zu LEAKS FOUND ! =====\e[0m\n", v->size);
}

void *ft_malloc(size_t size, int line, char *function, char *file) {
    void *(*libc_malloc)(size_t size) = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");
    void *p = libc_malloc(size);
    if (!p)
        return (NULL);
    v_add(v_malloc, p, line, function, file, size);
    return (p);
}

void ft_free(void *ptr) {
    void *(*libc_free)(void *ptr) = (void *(*)(void *)) dlsym(RTLD_NEXT, "free");
	if (ptr)
    	v_remove(v_malloc, ptr);
    libc_free(ptr);
}

void check_leaks(void) {
    if (v_malloc->size != 0)
    {
        v_puts(v_malloc);
    }
    else
    {
        printf("\e[32m\t===== NO LEAKS =====\n\e[0m");
    }
    v_clear(v_malloc);
}
