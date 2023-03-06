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
    if (clients[index].check_read) {
        int val = read(clients[index].data_fd, buf, 2048);
        write(clients[index].readfd, buf, val);
        if (val == 0) {
            close(clients[index].readfd);
            write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
            close(clients[index].original_data_fd);
            close(clients[index].data_fd);
            clients[index].original_data_fd = -1;
            clients[index].data_fd = -1;
        }
    }
}
