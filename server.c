/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** server
*/

#include "my.h"

void loop_server(int serversocket, t_clients *clients)
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
            if (FD_ISSET(serversocket, &rfds)) {
                int clientfd = accept(serversocket, (struct sockaddr *)&client,  (socklen_t*) (&addrlen));
                add_client(clients, false, clientfd);
                write(clientfd, "220 Service ready for new user.\n", 33);
                selectqueue--;
                if(!selectqueue) continue;
            }
            for (int i = 0; i!= 100; i++) {
                if (clients[i].original_data_fd >= 0 && FD_ISSET(clients[i].original_data_fd, &rfds)) {
                    write(1, "Here PASV connexion !", 22);
                    int clientfd = accept(clients[i].original_data_fd, (struct sockaddr *)&client,  (socklen_t*) (&addrlen));
                    clients[i].data_fd = clientfd;
                    write(clientfd, "Hello World !", 14);
                   // clients[i].original_data_fd = -1;
                    selectqueue--;
                    if(!selectqueue) continue;
                }
            }
           read_clients_control(&rfds, clients);
           read_clients_data(&rfds, clients);
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
        else if (clients[i].data_fd == -1 && data) {
            clients[i].data_fd = fd;
            break;
        }
    }
}

void add_clients_to_set(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i != 100; i++) {
        if (clients[i].control_fd != -1) {
            FD_SET(clients[i].control_fd, rfds);
        }
        if (clients[i].data_fd != -1) {
            FD_SET(clients[i].data_fd, rfds);
        }
        if (clients[i].original_data_fd != -1) {
            FD_SET(clients[i].original_data_fd, rfds);
        }
    }
}

void read_clients_control(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i!= 100; i++) {
        if (clients[i].control_fd > 0 && FD_ISSET(clients[i].control_fd, rfds)) {
            char buf[1000] = {0};
            int val = recv(clients[i].control_fd, buf, 1000, 0);
            buf[strlen(buf) - 2] = '\0';
            if (strcmp(buf, "PASV") == 0) {
                add_data_port_to_client(clients, clients[i].control_fd);
            }
            if (strncmp(buf, "RETR", 4) == 0) {
                do_retr_cmd(i, clients, buf);
            }
            if (val == 0) {
                puts("closing");
                close(clients[i].control_fd);
                clients[i].control_fd = -1;
            }
        }
    }
}

void read_clients_data(fd_set *rfds, t_clients *clients)
{
    for (int i = 0; i!= 100; i++) {
        if (clients[i].data_fd > 0 && FD_ISSET(clients[i].data_fd, rfds)) {
            char *buf;
            int val = recv(clients[i].data_fd, buf, 1000, 0);
            buf[strlen(buf) - 2] = '\0';
            write(1, buf, strlen(buf));
            write(clients[i].data_fd, "I heard you.", 12);
            if (val == 0) {
                puts("closing");
                close(clients[i].data_fd);
                clients[i].data_fd = -1;
            }
        }
    }
}

void add_data_port_to_client(t_clients *clients, int clientfd)
{
    for (int i = 0; i!= 100; i++) {
        if (clients[i].control_fd == clientfd) {
            struct sockaddr_in adress;
            int fd = create_data(&adress, clientfd);
            struct sockaddr_in local_address;
            int addr_size = sizeof(local_address);
            getsockname(fd, (struct sockaddr *)&local_address,  (socklen_t*) (&addr_size));
            clients[i].original_data_fd = fd;
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
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &(int){1}, sizeof(int));
    int bindval = bind(sockfd, (struct sockaddr *)adress, sizeof(struct sockaddr_in));
    int listen_return = listen(sockfd, 100);
    int datalen = sizeof(adress);
    getsockname(sockfd, (struct sockaddr *)adress,  (socklen_t*) (&datalen) );
    int client_port = ntohs(adress->sin_port);
    char *server_ip = inet_ntoa(adress->sin_addr);
    send_pasv_info(server_ip, client_port, clienFd);
    return sockfd;
}