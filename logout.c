/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** logout
*/

#include "my.h"

void do_logout(int index, t_clients *clients)
{
    write(clients[index].control_fd, LOGOUTMSG, strlen(LOGOUTMSG));
    close(clients[index].control_fd);
    if (clients[index].data_fd != -1)
        close(clients[index].data_fd);
    clients[index].control_fd = -1;
    clients[index].data_fd = -1;
    clients[index].original_data_fd = -1;
    clients[index].connected = false;
    clients[index].pass = NULL;
    clients[index].user = NULL;
    clients[index].buffer = NULL;
}
