/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** port_utils
*/

#include "my.h"

void free_port_val(char *ip, char **parsed)
{
    for (int i = 0; i != my_arrlen(parsed); i++)
        free(parsed[i]);
    free(ip);
}
