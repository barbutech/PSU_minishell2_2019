/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** structures.h
*/

#ifndef structures_h
#define structures_h

struct envnm
{
    char *name;
    char *value;
    struct envnm *head;
    struct envnm *next;
    struct envnm *prev;
};
typedef struct envnm envnm_t;

struct infos {
    char ***tableur;
    char **envp;
    int loc;
    int is_pipe;
    int last_return;
};
typedef struct infos infos_t;

#endif