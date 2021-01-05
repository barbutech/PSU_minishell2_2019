/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** my_strncmp.c
*/

int my_strncmp(char *s1, char *s2, int nbr)
{
    int size_s1 = 0;
    int size_s2 = 0;
    int size_end = 0;

    for (int tmp = 0; tmp < nbr; tmp++) {
        size_s1 += s1[tmp] - 48;
        size_s2 += s2[tmp] - 48;
    }
    size_end = size_s1 - size_s2;
    if (size_end != 0)
        return (size_end);
    for (int tmp = 0; tmp < nbr; tmp++)
        if (s1[tmp] != s2[tmp])
            return (-1);
    return (0);
}