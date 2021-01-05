/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_str_allocate_and_cat.c
*/

#include <stdlib.h>
#include <stdio.h>

char *my_str_allocate_and_cat(char *dest, char *src)
{
    int size_dest = 0;
    int size_src = 0;
    char *ret;
    int count = 0;

    for (; dest[size_dest] != '\0'; size_dest++);
    for (; src[size_src] != '\0'; size_src++);
    ret = malloc(sizeof(char) * (size_dest + size_src + 1));
    if (ret == NULL)
        return (NULL);
    ret[size_src + size_dest] = '\0';
    for (; dest[count] != '\0'; count++)
        ret[count] = dest[count];
    for (int tmp = 0; src[tmp] != '\0'; tmp++, count++)
        ret[count] = src[tmp];
    return (ret);
}