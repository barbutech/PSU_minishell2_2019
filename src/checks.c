/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** checks.c
*/

#include <unistd.h>
#include "../include/my.h"

int check_command(char **command)
{
    int count = 0;

    for (; command[count]; count++);
    for (int tmp = 0; command[1][tmp] != '\0'; tmp++) {
        if (command[1][tmp] == '=') {
            write(2, "setenv: Variable name must contain", 34);
            write(2, " alphanumeric characters.\n", 26);
            return (84);
        }
    }
    if (count <= 2)
        return (0);
    for (int tmp = 0; command[2][tmp] != '\0'; tmp++) {
        if (command[2][tmp] == '=') {
            write(2, "setenv: Variable name must contain", 34);
            write(2, " alphanumeric characters.\n", 26);
            return (84);
        }
    }
    return (0);
}

int replace(char *str, char *value, envnm_t **env)
{
    (*env) = (*env)->head;

    for (; my_strcmp(str, (*env)->name) != 0; (*env) = (*env)->next)
        if (!(*env)->next)
            return (0);
    (*env)->value = my_strdup(value);
    return (0);
}

char *is_ok(char **command, envnm_t *env)
{
    char *path = my_getenv(env, "PATH");
    char *ret = NULL;
    if (path == NULL) return (command[0]);
    char **the_pathes = my_str_to_word_array(path);
    free(path);

    if (the_pathes == NULL || the_pathes[0] == NULL)
        return (command[0]);
    for (int line = 0; the_pathes[line] != NULL; line++) {
        ret = my_str_allocate_and_cat(the_pathes[line], "/");
        ret = my_str_allocate_and_cat(ret, command[0]);
        if (access(ret, F_OK) == 0)
            break;
    }
    for (int count = 0; the_pathes[count]; count++)
        free(the_pathes[count]);
    if (access(ret, F_OK) == 0)
        return (ret);
    free(ret);
    return (command[0]);
}