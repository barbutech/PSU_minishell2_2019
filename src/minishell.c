/*
** EPITECH PROJECT, 2019
** Minishell1
** File description:
** minishell.c
*/

#include "../include/my.h"

int execve_part(char *way, infos_t **infos, envnm_t *env)
{
    int stat_loc = 0;
    __pid_t pid_son;
    int pfd[2];
    pipe(pfd);

    if ((pid_son = fork()) == 0) {
        if (is_there_a_pipe(&(*infos), pfd, env) != -2) exit(0);
        in_the_son(pfd, (*infos)->tableur[(*infos)->loc], (*infos)->envp);
        if (check_input(pfd, (*infos)->tableur[(*infos)->loc]) == 84) exit (1);
        execve(way, (*infos)->tableur[(*infos)->loc], (*infos)->envp);
        print_error_and_exit_son(way, pid_son);
    }
    else {
        close(pfd[1]);
        waitpid(pid_son, &stat_loc, 0);
    }
    return (stat_loc);
}

int exec_for_me(char *way, infos_t **infos, envnm_t *env)
{
    int stat_loc = 0;
    int count = 0;

    stat_loc = execve_part(way, &(*infos), env);
    if (stat_loc == 11)
        write(2, "Segmentation fault\n", 19);
    if (stat_loc == 139)
        write(2, "Segmentation fault (core dumped)\n", 33);
    if (stat_loc == 136)
        write(2, "Floating exception (core dumped)\n", 33);
    if (stat_loc == 8)
        write(2, "Floating exception\n", 19);
    for (; (*infos)->tableur[(*infos)->loc][count]; count++);
    if (my_strcmp((*infos)->tableur[(*infos)->loc][count - 1], "|") == 0)
        (*infos)->is_pipe = 1;
    return (WEXITSTATUS(stat_loc));
}

int builtins(infos_t *infos, envnm_t **env)
{

    if (my_strcmp(infos->tableur[infos->loc][0], "exit") == 0) {
        write (1, "exit\n", 5);
        exit (EXIT_SUCCESS);
    }
    if (my_strcmp(infos->tableur[infos->loc][0], "env") == 0 )
        return (case_of_env((*env)));
    if (my_strcmp(infos->tableur[infos->loc][0], "setenv") == 0 )
        return (case_of_setenv(infos->tableur[infos->loc], env));
    if (my_strcmp(infos->tableur[infos->loc][0], "unsetenv") == 0)
        return (case_of_unsetenv(infos->tableur[infos->loc], env));
    if (my_strcmp(infos->tableur[infos->loc][0], "cd") == 0) {
        if (case_of_cd(infos->tableur[infos->loc], env) == 84)
            write(2, "cd: Too many arguments.\n", 24);
        return (0);
    }
    return (-1);
}

int loop(infos_t *infos, envnm_t *env)
{
    char *way;
    int value = -1;

    for (infos->loc = 0; infos->tableur[infos->loc]; infos->loc++) {
        if ((value = builtins(infos, &env)) == 84)
            return (value);
        else if (value -= -1)
            continue;
        if ((way = is_ok(infos->tableur[infos->loc], env)) == NULL)
            return (84);
        infos->last_return = exec_for_me(way, &infos, env);
        free(infos->tableur[infos->loc]);
        if (infos->is_pipe) infos->loc++;
        infos->is_pipe = 0;
    }
    return (0);
}

int main (int argc, char **argv, char **envp)
{
    error_env(envp);
    char *answer = NULL;
    size_t n = 0;
    infos_t *infos = malloc(sizeof(infos_t));
    infos->envp = envp;
    infos->is_pipe = 0;
    infos->last_return = 0;
    envnm_t *env = fill_name(envp);

    while (1) {
        write(0, "\e[33mprompt_t>:\e[0m", 19);
        if (getline(&answer, &n, stdin) == EOF)
            return (infos->last_return);
        infos->tableur = fill_the_command(infos->tableur, answer);
        if (loop(infos, env) == 84)
            return (84);
    }
}