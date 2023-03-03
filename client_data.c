/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** client_data
*/

#include "my.h"

void clear_client_data(int index, t_clients *clients)
{
    if (clients[index].data_fd != -1)
        close(clients[index].data_fd);
    if (clients[index].original_data_fd != -1)
        close(clients[index].original_data_fd);
    clients[index].check_read = false;
    clients[index].data_fd = -1;
    clients[index].data_port = -1;
    clients[index].original_data_fd = -1;
}

int does_client_has_data(int index, t_clients *clients)
{
    if (clients[index].data_fd == -1 &&
    clients[index].original_data_fd == -1) {
        write(clients[index].control_fd, NODATA, strlen(NODATA));
        return 0;
    }
    return 1;
}
