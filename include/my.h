/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** my
*/

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <strings.h>
#ifndef MY_H_
    #define MY_H_
struct clients {
    int data_fd;
    int control_fd;
    int data_port;
    int original_data_fd;
    bool connected;
    char *user;
    char *pass;
} typedef t_clients;
int create_server(void);
void loop_server(int serversocket, t_clients *clients);
void add_client(t_clients *clients, bool data, int fd);
void add_clients_to_set(fd_set *rfds, t_clients *clients);
void read_clients_control(fd_set *rfds, t_clients *clients);
char *my_itoa(int val, char *buffer);
void send_pasv_info(char *adress, int port, int fd);
int create_data(struct sockaddr_in *adress, int clienFd);
char *my_revstr(char *src);
void add_data_port_to_client(t_clients *clients, int clientfd);
void read_clients_data(fd_set *rfds, t_clients *clients);
void do_retr_cmd(int index, t_clients *clients, char *buf);
int is_client_logged_in(int index, t_clients *clients);
void handle_client_control(int index, t_clients *clients);
void do_user_cmd(int index, t_clients *clients, char *buf);
void do_pass_cmd(int index, t_clients *clients, char *buf);
int is_login_or_pass(char *buf);
#endif /* !MY_H_ */
