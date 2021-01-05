/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_modified_strncpy.c
*/

#include <stdlib.h>

char *my_strndup(char *src, int n)
{
    char *ret;
    int size = 0;
    int tmp = 0;

    for (; tmp < n; tmp++);
    for (; src[tmp] != '\0'; tmp++, size++);
    ret = malloc(sizeof(char) * (size + 1));
    ret[size] = '\0';
    for (int count = 0; src[n] != '\0'; count++, n++)
        ret[count] = src[n];
    return (ret);
}