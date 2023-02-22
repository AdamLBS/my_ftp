/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** quit
*/

#include "my.h"

void do_quit_cmd(int index, t_clients *clients)
{
    write(clients[index].control_fd, QUITMSG, strlen(QUITMSG));
    close(clients[index].control_fd);
    clients[index].control_fd = -1;
}
