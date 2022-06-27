/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:58:02 by bgenie            #+#    #+#             */
/*   Updated: 2022/06/23 13:53:20 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks.h"

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

static vector *v_add(vector *v, void *p) {
    if (v->size >= v->max_size)
        v = v_resize(v, v->max_size + 1);
    v->ptr[v->size] = p;
    v->size++;
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
    for (size_t i = 0; i < v->size; ++i)
        dprintf(2, "%lu: [%p]\n", i, v->ptr[i]);
}

void *malloc(size_t size) {

    void *(*libc_malloc)(size_t size) = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");
    void *p = libc_malloc(size);
    if (!p)
        return (NULL);
    v_add(&v_malloc, p);
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
        dprintf(2, "\e[31mLEAKS!\n\e[0m");
        dprintf(2, "\e[31m");
        v_puts(&v_malloc);
        dprintf(2, "\e[0m");
    }
    else
        dprintf(2, "\e[32mNO LEAKS :D\n\e[0m");
	v_clear(&v_malloc);
}
