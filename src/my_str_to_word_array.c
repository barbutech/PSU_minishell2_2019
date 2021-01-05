/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** my_str_to_word_array.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"

int number_of_words(char *str)
{
    int nbr_of_words = 0;
    static int x = 0;

    for (; str[x] != '\0' && str[x] != '\n';) {
        for (; str[x] == ':' || str[x] == ' ' || str[x] == '\t'; x++);
        for (; str[x] != ':' && str[x] != ' ' && str[x] != '|' &&
        str[x] != '\0' && str[x] != '\t' && str[x] != ';'; x++);
        nbr_of_words++;
        if (str[x] == '\0') {
            x = 0;
            return (nbr_of_words);
        }
        for (; str[x] == ':' || str[x] == ' ' || str[x] == '\t'; x++);
        if (str[x] == ';' || str[x] == '|') {
            x++;
            return (nbr_of_words + 1);
        }
    }
    x = 0;
    return (nbr_of_words);
}

char *fill_line(char *str, int count, int nbr, int tmp)
{
    int pos = 0;
    char *ret = malloc(sizeof(char) * (nbr + 1));

    if (ret == NULL)
        return (NULL);
    for (; tmp < count; tmp++, pos++) {
        for (; str[tmp] == '\t' || str[tmp] == ' '; tmp++);
        ret[pos] = str[tmp];
    }
    ret[pos] = '\0';
    return (ret);
}

char *fill_tab(char *str, char **word_tab, int p)
{
    static int x = 0;
    static int tmp = 0;
    int nbr = 0;

    if (str[x] == ';') {
        word_tab[p] = ";";
        x++;
        tmp++;
        return (word_tab[p]);
    }
    for (; str[x] == ':' || str[x] == ' ' || str[x] == '\t'; x++);
    for (; str[x] != ' ' && str[x] != ':' && str[x] != ';' &&
    str[x] != '\0' && str[x] != '\n' && str[x] != '\t'; x++)
        nbr++;
    word_tab[p] = fill_line(str, x, nbr, tmp);
    for (; str[x] == ' ' || str[x] == ':' || str[x] == '\n' ||
    str[x] == '\t'; x++);
    tmp = x;
    str[x] == '\0' ? tmp = 0 : 0;
    str[x] == '\0' ? x = 0 : 0;
    return (word_tab[p]);
}

char **my_str_to_word_array(char *str)
{
    int nbr_of_words = number_of_words(str);
    if (nbr_of_words == 0) return (NULL);
    char **word_tab = malloc(sizeof(char *) * (nbr_of_words + 1));
    int count = 0;

    if (word_tab == NULL)
        return (NULL);
    word_tab[nbr_of_words] = NULL;
    for (; count < nbr_of_words; count++)
        fill_tab(str, word_tab, count);
    if (my_strcmp(word_tab[nbr_of_words - 1], ";") == 0)
        word_tab[nbr_of_words - 1] = NULL;
    return (word_tab);
}