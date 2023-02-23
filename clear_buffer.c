/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** clear_buffer
*/

#include "my.h"

void clear_buffer(int index, t_clients *clients)
{
    free(clients[index].buffer);
    clients[index].buffer = NULL;
}