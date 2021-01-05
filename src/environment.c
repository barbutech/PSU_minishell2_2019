/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** environment.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/structures.h"
#include "../include/my.h"

char *set_value(char **envp, int line, int count)
{
    char *value;
    int tmp = count;
    int alloc;

    for (; envp[line][count] != '\0'; count++);
    alloc = count - tmp;
    value = malloc(sizeof(char) * alloc);
    value[alloc - 1] = '\0';
    tmp++;
    for (int loc = 0; envp[line][tmp] != '\0'; loc++, tmp++)
        value[loc] = envp[line][tmp];
    return (value);
}

envnm_t *fill_name(char **envp)
{
    int count = 0;
    char *name;
    char *value;
    envnm_t *ret = NULL;

    for (int line = 0; envp[line] != NULL; line++) {
        for (; envp[line][count] != '='; count++);
        name = malloc(sizeof(char) * (count + 1));
        name[count] = '\0';
        for (int tmp = 0; tmp < count; tmp++)
            name[tmp] = envp[line][tmp];
        value = set_value(envp, line, count);
        stack_push(&ret, name, value);
        count = 0;
    }
    ret = ret->head;
    return (ret);
}

int case_of_setenv(char **command, envnm_t **env)
{
    int count = 0;
    if (!(command[1]))
        return (case_of_env((*env)));
    for (; command[count]; count++);
    if (count > 3) return (0);
    if (check_command(command) == 84)
        return (84);
    (*env) = (*env)->head;
    for (; (*env);) {
        if (there_is_a_value(env, command) == 0)
            return (0);
        if (!((*env)->next))
            break;
        (*env) = (*env)->next;
    }
    if (command[2])
    stack_push(env, my_strdup(command[1]), my_strdup(command[2]));
    else
        stack_push(env, my_strdup(command[1]), "");
    return (0);
}

int case_of_env(envnm_t *env)
{
    env = env->head;
    for (; env; env = env->next) {
        my_putstr(env->name);
        write(1, "=", 1);
        my_putstr(env->value);
        write(1, "\n", 1);
        if (env->next == NULL)
            return (0);
    }
    return (0);
}

int case_of_unsetenv(char **command, envnm_t **env)
{
    (*env) = (*env)->head;
    for (; (*env); (*env) = (*env)->next) {
        if (my_strcmp(command[1], (*env)->name) == 0) {
            stack_pop(env);
            return (0);
        }
        if ((*env)->next == NULL)
            return (0);
    }
    return (0);
}