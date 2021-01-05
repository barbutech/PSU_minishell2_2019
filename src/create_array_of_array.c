/*
** EPITECH PROJECT, 2019
** PSU
** File description:
** 3d_array_and_checks.c
*/

#include "../include/my.h"

int in_the_son(int *pipefd, char **com, char **envp)
{
    int loc = 0;
    int fd = 0;
    close(pipefd[0]);

    for (; com[loc]; loc++) {
        if (!(com[loc])) continue;
        if (case_output(fd, com, loc, envp) == -1)
            return (84);
    }
    return (0);
}

int check_input(int *pipefd, char **com)
{
    int loc = 0;
    int fd = 0;
    int count = 0;

    for (; com[loc]; loc++) {
        if (!(com[loc])) continue;
        if (is_there_an_error(fd, com, loc, count) == -1) return (-1);
    }
    return (0);
}

int search_nbr_of_tab(char *answer)
{
    int count = 0;
    int nbr_of_tab = 1;
    int is_something = 0;

    for (; answer[count] != '\0'; count++) {
        if (answer[count] != ' ' && answer[count] != '\t' &&
        answer[count] != '\n')
            is_something = 1;
        if (answer[count] == ';' || answer[count] == '|')
            nbr_of_tab++;
    }
    if (is_something == 0)
        nbr_of_tab = 0;
    return (nbr_of_tab);
}

char ***fill_the_command(char ***tableur, char *answer)
{
    int nbr_of_tab = search_nbr_of_tab(answer);

    tableur = malloc(sizeof(char **) * (nbr_of_tab + 1));
    if (nbr_of_tab == 0)
        return (tableur);
    for (int count = 0; count < nbr_of_tab; count++) {
        tableur[count] = my_str_to_word_array(answer);
        if (tableur[count] == NULL)
            exit (84);
    }
    tableur[nbr_of_tab] = NULL;
    return (tableur);
}