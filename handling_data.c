/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** handling_data
*/

#include "my.h"

void handling_data_socket(int index, t_clients *clients)
{
    char buf[2048] = {0};
    size_t byte = 0;
    if (!clients[index].check_read || clients[index].data_fd == -1)
        return;
    while (1) {
        byte = read(clients[index].data_fd, buf, 2048);
        if (byte == -1 || byte == 0) {
            break;
        }
        write(clients[index].readfd, buf, byte);
        memset(buf, 0, 2048);
    }
    close(clients[index].readfd);
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
    clear_client_data(index, clients);
}
