/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** my.h
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "structures.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_putstr(char *);
char ** my_str_to_word_array(char *);
char *my_getenv(envnm_t *env, char *elem);
char *my_str_allocate_and_cat(char *, char *);
int my_strcmp(char *, char *);
void stack_push(envnm_t **, char *, char *);
void stack_pop(envnm_t **env);
envnm_t *fill_name(char **);
int case_of_env(envnm_t *env);
int case_of_unsetenv(char **command, envnm_t **env);
int case_of_setenv(char **, envnm_t **env);
int my_strlen(char *);
char *my_strdup(char *str);
int my_strncmp(char *, char *, int);
int case_of_cd(char **command, envnm_t **env);
char *my_strndup(char *, int);
void error_env(char **);
int replace(char *str, char *value, envnm_t **env);
int there_is_a_value(envnm_t **env, char **command);
int in_the_son(int *pipefd, char **com, char **envp);
int check_input(int *pipefd, char **com);
int search_nbr_of_tab(char *answer);
char ***fill_the_command(char ***tableur, char *answer);
int case_output(int fd, char **com, int loc, char **envp);
int is_there_an_error(int fd, char **com, int loc, int count);
int check_command(char **command);
int is_there_a_pipe(infos_t **infos, int *pipefd, envnm_t *env);
char *is_ok(char **command, envnm_t *env);
int print_error_and_exit_son(char *way, int pid_son);