/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** unknown
*/

#include "my.h"

void do_unknown_cmd(int index, t_clients *clients)
{
    write(clients[index].control_fd, UNKNOWN, strlen(UNKNOWN));
}
