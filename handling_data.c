/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** handling_data
*/

#include "my.h"

void handling_data_socket(int index, t_clients *clients)
{
    char buf[BUFSIZ] = {0};
    if (clients[index].check_read) {
        int val = read(clients[index].data_fd, buf, BUFSIZ);
        if (val == 0) {
            fclose(clients[index].readfd);
            write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
            clear_client_data(index, clients);
            return;
        }
        fwrite(buf, 1, val, clients[index].readfd);
    }
}
