/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** case_of_cd.c
*/

#include "../include/my.h"
#include "../include/structures.h"
#include <stdio.h>

int execute_cd(envnm_t **env, char **command)
{
    char *path = my_getenv((*env), "PWD");
    char *old_pwd = getcwd(NULL, 0);
    char * new_path = my_str_allocate_and_cat(path, "/");
    char *new_pwd;

    new_path = my_str_allocate_and_cat(new_path, command[1]);
    if (chdir(new_path) == 0)
        new_pwd = getcwd(NULL, 0);
    else
        return (-1);
    replace("PWD", new_pwd, env);
    replace("OLDPWD", old_pwd, env);
    free(path);
    free(new_path);
    return (0);
}

int case_of_cd_malus(envnm_t **env)
{
    char *tmp = my_getenv((*env), "OLDPWD");
    char *current_pwd = getcwd(NULL, 0);

    if (chdir(tmp) == -1)
        return (-1);

    replace("OLDPWD", current_pwd, env);
    replace("PWD", tmp, env);
    return (0);
}

int case_of_home(envnm_t **env)
{
    char *home = my_getenv((*env), "HOME");
    char *old = getcwd(NULL, 0);

    if (chdir(home) == -1)
        return (-1);
    replace("PWD", home, env);
    replace("OLDPWD", old, env);
    return (0);
}

int case_of_absolute(envnm_t **env, char **command)
{
    char *old = getcwd(NULL, 0);

    if (chdir(command[1]) == -1) {
        my_putstr(command[1]);
        write(2, ": Not a directory.\n", 19);
        return (-1);
    }

    replace("PWD", command[1], env);
    replace("OLDPWD", old, env);
    return (0);
}

int case_of_cd(char **command, envnm_t **env)
{
    int count = 0;

    for (; command[count]; count++);
    if (count >= 3) return (84);
    (*env) = (*env)->head;
    if (!(command[1]) || my_strcmp(command[1], "~") == 0 ||
    my_strcmp(command[1], "--") == 0)
        return (case_of_home(env));
    if (my_strcmp(command[1], "-") == 0)
        return (case_of_cd_malus(env));
    if (command[1][0] == '/')
        return (case_of_absolute(env, command));
    if (execute_cd(env, command) == -1)
        return (-1);
    return (0);
}