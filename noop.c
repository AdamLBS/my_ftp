/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** noop
*/

#include "my.h"


void do_noop(int index, t_clients *clients)
{
    write(clients[index].control_fd, MSGOKAY, strlen(MSGOKAY));
}
