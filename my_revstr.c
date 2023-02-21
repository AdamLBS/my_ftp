/*
** EPITECH PROJECT, 2021
** my_revstr.c
** File description:
** my_revstr
*/

#include "my.h"

char *my_revstr(char *src)
{
    int i = 0;
    char aux;

    while (src[i] != '\0')
        i++;
    for (int j = 0; j < i; j++, i--) {
        aux = src[j];
        src[j] = src[i - 1];
        src[i - 1] = aux;
    }
    return src;
}
