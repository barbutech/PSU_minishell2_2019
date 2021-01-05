/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** linked_list.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/structures.h"
#include "../include/my.h"

void stack_push(envnm_t **envp, char *name, char *value)
{
    envnm_t *new = malloc(sizeof(envnm_t));

    new->name = name;
    new->value = value;
    new->next = NULL;

    if ((*envp) == NULL) {
        (*envp) = new;
        (*envp)->prev = NULL;
        (*envp)->head = (*envp);
        return ;
    }
    new->prev = (*envp);
    new->prev->next = new;
    new->head = (*envp)->head;
    (*envp) = new;
    return ;
}

void stack_pop(envnm_t **env)
{
    if ((*env) == NULL)
        return ;
    if ((*env)->prev == NULL) {
        (*env) = NULL;
        return;
    }
    if ((*env)->next != NULL) {
        (*env)->next->prev = (*env)->prev;
        (*env)->prev->next = (*env)->next;
    }
    (*env) = (*env)->prev;
    (*env)->next = NULL;
}

void error_env(char **envp)
{
    int count = 0;

    for (; envp[count]; count++);
    if (count < 2)
        exit (EXIT_SUCCESS);
}

int there_is_a_value(envnm_t **env, char **command)
{
    if (my_strcmp((*env)->name, command[1]) == 0) {
        if (command[2])
            (*env)->value = my_strdup(command[2]);
        else
            (*env)->value = "";
        return (0);
    }
    return (1);
}