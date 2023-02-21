/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** client_control
*/

#include "my.h"

int is_client_logged_in(int index, t_clients *clients)
{
    if (clients[index].connected == false) {
        char *msg = strdup("530 Please login with USER and PASS.\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return 0;
    }
    return 1;
}

void handle_client_control(int index, t_clients *clients)
{
    char buf[1000] = {0};
    int val = read(clients[index].control_fd, buf, 1000);
    if (strcmp(buf, "LOGOUT\r\n") == 0)
        do_logout(index, clients);
    if (is_login_or_pass(buf) == 0 && !is_client_logged_in(index, clients))
        buf[0] = '\0';
    check_cmds(index, clients, buf);
    if (val == 0) {
        puts("closing");
        close(clients[index].control_fd);
        clients[index].control_fd = -1;
    }
}

void check_cmds(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "PASV\r\n") == 0)
        add_data_port_to_client(clients, clients[index].control_fd);
    if (strcmp(buf, "NOOP\r\n") == 0)
        do_noop(index, clients);
    if (strncmp(buf, "RETR", 4) == 0)
        do_retr_cmd(index, clients, buf);
    if (strncmp(buf, "USER", 4) == 0)
        do_user_cmd(index, clients, buf);
    if (strncmp(buf, "PASS", 4) == 0)
        do_pass_cmd(index, clients, buf);
    if (strcmp(buf, "PWD\r\n") == 0)
        do_pwd(index, clients);
    if (strcmp(buf, "LIST\r\n") == 0)
        do_list(index, clients);
}
