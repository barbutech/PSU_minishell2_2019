/*
** EPITECH PROJECT, 2019
** PSU
** File description:
** inputs_and_outputs.c
*/

#include "../include/my.h"

int create_file(char *str, char **envp)
{
    pid_t pid;
    int stat_loc = 0;
    char *create[] = {"touch", str, NULL};

    if ((pid = fork()) == 0) {
        execve("/usr/bin/touch", create, envp);
    }
    else
        waitpid(pid, &stat_loc, 0);
    return (0);
}

int case_output(int fd, char **com, int loc, char **envp)
{
    if (my_strcmp(com[loc], ">") == 0 || my_strcmp(com[loc], ">>") == 0) {
        if (!(com[loc + 1])) return (84);
        if (access(com[loc + 1], F_OK) == -1)
            create_file(com[loc + 1], envp);
        my_strcmp(com[loc], ">") == 0 ? fd = open(com[loc + 1], O_WRONLY) : 0;
        if (my_strcmp(com[loc], ">>") == 0)
            fd = open(com[loc + 1], O_WRONLY | O_APPEND);
        dup2(fd, 1);
        com[loc + 1] = NULL;
        com[loc] = NULL;
        loc += 1;
        close(fd);
    }
        return (fd);
}

int is_there_an_error(int fd, char **com, int loc, int count)
{
    if (my_strcmp(com[loc], "<") == 0) {
            if (!(com[loc + 1]) || com[loc + 2]) {
            write(2, "Il manque un nom pour rediriger.\n", 33);
            return (-1);
            }
        fd = open(com[loc + 1], O_RDONLY);
        if (fd == -1) {
            for (; com[loc + 1][count] != '\0'; count++);
            write(2, com[loc + 1], count);
            write(2, ": No such file or directory.\n", 29);
            return (-1);
        }
            dup2(fd, 0);
        com[loc + 1] = NULL;
        com[loc] = NULL;
        loc += 1;
        close(fd);
        }
        return (fd);
}

int print_error_and_exit_son(char *way, int pid_son)
{
    if (errno == 2) {
            my_putstr(way);
            write(2, ": Command not found.\n", 21);
        }
    if (errno == 8) {
            my_putstr(way);
            write(2, ": Exec format error. Wrong Architecture.\n", 41);
        }
    if (errno == 13) {
            my_putstr(way);
            write(2, ": Permission denied.\n", 21);
        }
    if (errno != 8 && errno != 2 && errno != 13)
        perror(way);
    kill(pid_son, 0);
    exit (0);
}