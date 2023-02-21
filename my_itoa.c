/*
** EPITECH PROJECT, 2021
** B-MUL-100-MAR-1-1-myhunter-adam.elaoumari
** File description:
** my_itoa
*/

#include "my.h"

int get_intlen(int val)
{
    int nb = 0;
    while (val != 0) {
        val = val / 10;
        nb++;
    }
    return nb;
}

char *my_itoa(int val, char *buffer)
{
    int len = get_intlen(val);
    int i = 0;
    if (val == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    while (len != 0) {
        buffer[i++] = val % 10 + 48;
        val = val / 10;
        len--;
    }
    buffer[i] = '\0';
    my_revstr(buffer);
    return buffer;
}
