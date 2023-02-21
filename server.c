/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** server
*/

#include "my.h"

void loop_server(int serversocket, t_clients *clients, t_server *server)
{
    fd_set rfds;
    struct sockaddr_in adress, client, data;
    int addrlen = sizeof(adress), datalen = sizeof(data);
    FD_SET(serversocket, &rfds);
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(serversocket, &rfds);
        add_clients_to_set(&rfds, clients);
        int selectqueue = select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
        if (selectqueue >= 0) {
            check_server_connections(serversocket, &rfds, clients,
            &selectqueue);
            check_data_connections(&rfds, clients, &selectqueue);
            read_sockets(&rfds, clients, selectqueue);
        }
    }
}

void add_client(t_clients *clients, bool data, int fd)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].control_fd == -1 && data == false) {
            clients[i].control_fd = fd;
            break;
        }
        if (clients[i].data_fd == -1 && data) {
            clients[i].data_fd = fd;
            break;
        }
    }
}

void add_clients_to_set(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].control_fd != -1)
            FD_SET(clients[i].control_fd, rfds);
        if (clients[i].data_fd != -1)
            FD_SET(clients[i].data_fd, rfds);
        if (clients[i].original_data_fd != -1)
            FD_SET(clients[i].original_data_fd, rfds);
    }
}
