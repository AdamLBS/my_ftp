/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** server_utils
*/

#include "my.h"

void read_clients_control(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].control_fd > 0 &&
            FD_ISSET(clients[i].control_fd, rfds))
            handle_client_control(i, clients);
    }
}

void read_clients_data(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].data_fd > 0 &&
            FD_ISSET(clients[i].data_fd, rfds)) {
                handling_data_socket(i, clients);
        }
    }
}

void add_data_port_to_client(t_clients *clients, int clientfd)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].control_fd == clientfd) {
            clear_client_data(i, clients);
            struct sockaddr_in adress;
            int fd = create_data(&adress, clientfd);
            struct sockaddr_in local_address;
            int addr_size = sizeof(local_address);
            getsockname(fd, (struct sockaddr *)&local_address,
            (socklen_t*) (&addr_size));
            clients[i].original_data_fd = fd;
            clients[i].buffer = NULL;
        }
    }
}

int create_data(struct sockaddr_in *adress, int clienFd)
{
    adress->sin_port = htons(0);
    adress->sin_family = AF_INET;
    adress->sin_addr.s_addr = INADDR_ANY;
    int retval;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &(int){1},
    sizeof(int));
    int bindval = bind(sockfd, (struct sockaddr *)adress,
    sizeof(struct sockaddr_in));
    int listen_return = listen(sockfd, 100);
    int datalen = sizeof(adress);
    getsockname(sockfd, (struct sockaddr *)adress,  (socklen_t*) (&datalen) );
    int client_port = ntohs(adress->sin_port);
    getsockname(clienFd, (struct sockaddr *)adress,  (socklen_t*) (&datalen) );
    struct in_addr ipaddr = adress->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &ipaddr, str, INET_ADDRSTRLEN );
    send_pasv_info(str, client_port, clienFd);
    return sockfd;
}

void read_sockets(fd_set *rfds, t_clients *clients, int selectqueue)
{
    if (!selectqueue)
        return;
    read_clients_control(rfds, clients);
    read_clients_data(rfds, clients);
}
