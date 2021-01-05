/*
** EPITECH PROJECT, 2019
** my_strcmp
** File description:
** compare strings
*/

int my_strcmp(char *s1, char *s2)
{
    int m = 0;
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i = i + 1;
    m = s1[i] - s2[i];
    return (m);
}