/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** pipes.c
*/

#include "../include/my.h"

int exec_pipe(int pid, infos_t **infos, int *pipefd, envnm_t *env)
{
    char *way;

    if (pid == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], 1) < 0) return (84);
        if ((way = is_ok((*infos)->tableur[(*infos)->loc], env)) == NULL)
            return (84);
        execve(way, (*infos)->tableur[(*infos)->loc], (*infos)->envp);
        exit (0);
    }
    else {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        if ((way = is_ok((*infos)->tableur[(*infos)->loc + 1], env)) == NULL)
            return (84);
        execve(way, (*infos)->tableur[(*infos)->loc + 1], (*infos)->envp);
    }
    return (0);
}

int is_there_a_pipe(infos_t **infos, int *pipefd, envnm_t *env)
{
    int count = 0;
    int pid;

    for (; (*infos)->tableur[(*infos)->loc][count]; count++);
    if (my_strcmp((*infos)->tableur[(*infos)->loc][count - 1], "|") != 0)
        return (-2);
    if (!(*infos)->tableur[(*infos)->loc + 1]) return (84);
    (*infos)->tableur[(*infos)->loc][count - 1] = NULL;
    if ((pid = fork()) < 0) return (84);
    if (exec_pipe(pid, infos, pipefd, env) == 84)
        return (84);
    return (0);
}