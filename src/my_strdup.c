/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_strdup.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *my_strdup(char *str)
{
    char *ret;
    int count = 0;

    for (; str[count] != '\0'; count++);
    ret = malloc(sizeof(char) * count + 1);
    ret[count] = '\0';
    for (count = 0; str[count] != '\0'; count++)
        ret[count] = str[count];
    free(str);
    return (ret);
}