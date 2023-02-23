/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** server_utils2
*/

#include "my.h"

void check_if_client_closed(int index, t_clients *clients, int val)
{
    if (val == 0 && clients[index].data_fd) {
        close(clients[index].data_fd);
        clients[index].data_fd = -1;
        clients[index].check_read = false;
    }
}
