/*
** EPITECH PROJECT, 2021
** my_getnbr.c
** File description:
** getnbr
*/

#include "my.h"

int my_getnbr(char *str)
{
    int i = 0, result = 0;
    while ((str[i] >= '0' && str[i] <= '9')) {
        result = result * 10;
        result = result + str[i] - 48;
        i = i + 1;
    }
    return (result);
}

int my_getnbr_pos(char *str, int i)
{
    int result = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10;
        result = result + str[i] - 48;
        i = i + 1;
    }
    return (result);
}
