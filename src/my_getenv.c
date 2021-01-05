/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_getenv.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/structures.h"
#include "../include/my.h"

char *my_getenv(envnm_t *env, char *elem)
{
    char *path;
    int count = 0;

    env = env->head;
    if (!(env)) exit (84);
    for (; my_strcmp(env->name, elem) != 0;) {
        if (env->next == NULL) {
            return (NULL);
        }
    env = env->next;
    }
    for (; env->value[count] != '\0'; count++);
    path = malloc(sizeof(char) * (count + 1));
    path[count] = '\0';
    for (int mem = 0; env->value[mem] != '\0'; mem++)
        path[mem] = env->value[mem];
    return (path);
}