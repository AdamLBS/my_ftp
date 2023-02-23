/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** create_buffer
*/

#include "my.h"

void create_buffer(int index, t_clients *clients)
{
    if (clients[index].buffer == NULL) {
        clients[index].buffer = malloc(sizeof(char) * 1000);
        memset(clients[index].buffer, 0, 1000);
    }
}