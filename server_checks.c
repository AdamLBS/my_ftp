/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** server_checks
*/

#include "my.h"

int check_server_connections(int serversocket, fd_set *rfds,
t_clients *clients, int *selectqueue)
{
    if (!selectqueue)
        return 0;
    struct sockaddr_in adress, client, data;
    int addrlen = sizeof(adress), datalen = sizeof(data);
    if (FD_ISSET(serversocket, rfds)) {
        int clientfd = accept(serversocket, (struct sockaddr *)&client,
        (socklen_t*) (&addrlen));
        add_client(clients, false, clientfd);
        write(clientfd, "220 Service ready for new user.\r\n", 33);
        selectqueue--;
    }
    return 0;
}

int check_data_connections(fd_set *rfds, t_clients *clients, int *selectqueue)
{
    if (!selectqueue)
        return 0;
    struct sockaddr_in adress, client, data;
    int addrlen = sizeof(adress), datalen = sizeof(data);
    for (int i = 0; i != 100; i++) {
        if (clients[i].original_data_fd >= 0 &&
        FD_ISSET(clients[i].original_data_fd, rfds)) {
            int clientfd = accept(clients[i].original_data_fd,
            (struct sockaddr *)&client,(socklen_t*) (&addrlen));
            clients[i].data_fd = clientfd;
            selectqueue--;
        }
    }
    return 0;
}
