/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_strlen.c
*/

int my_strlen(char *str)
{
    int count = 0;

    for (; str[count] != '\0'; count++);
    return (count);
}