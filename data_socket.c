/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** data_socket
*/

#include "my.h"

void accept_data(int index, t_clients *clients)
{
    if (clients[index].pasv) {
        struct sockaddr_in client_addr = {0};
        socklen_t client_addr_len = sizeof(client_addr);
        clients[index].data_fd = accept(clients[index].original_data_fd,
        (struct sockaddr*)&client_addr, &client_addr_len);
    } else {
        struct sockaddr_in data_addr;
        int datalen = sizeof(data_addr);
        int port = clients[index].activ_port;
        data_addr.sin_addr.s_addr = inet_addr(clients[index].activ_ip);
        my_put_nbr(port);
        data_addr.sin_port = htons(port);
        data_addr.sin_family = AF_INET;
        clients[index].data_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (check_port_connection(clients, index,
        data_addr, clients[index].activ_ip))
            return;
        clients[index].original_data_fd = clients[index].data_fd;
    }
}
