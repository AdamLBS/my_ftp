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
    if (val == 0 && clients[index].control_fd) {
        close(clients[index].control_fd);
        clients[index].control_fd = -1;
    }
    if (check_cmds_nologin(index, clients, buf))
        return;
    if (strcmp(buf, "LOGOUT\r\n") == 0 )
        do_logout(index, clients);
    if (is_login_or_pass(buf) == 0 && !is_client_logged_in(index, clients))
        buf[0] = '\0';
    check_cmds(index, clients, buf);

}

void check_cmds(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "PASV\r\n") == 0) {
        add_data_port_to_client(clients, clients[index].control_fd);
        return;
    }
    if (strcmp(buf, "NOOP\r\n") == 0) {
        do_noop(index, clients);
        return;
    }
    if (strncmp(buf, "RETR", 4) == 0) {
        do_retr_cmd(index, clients, buf);
        return;
    }
    if (strncmp(buf, "USER", 4) == 0) {
        do_user_cmd(index, clients, buf);
        return;
    }
    check_cmds2(index, clients, buf);
}

void check_cmds2(int index, t_clients *clients, char *buf)
{
    if (strncmp(buf, "PASS", 4) == 0) {
        do_pass_cmd(index, clients, buf);
        return;
    }
    if (strcmp(buf, "PWD\r\n") == 0) {
        do_pwd(index, clients);
        return;
    }
    if (strcmp(buf, "LIST\r\n") == 0) {
        do_list(index, clients);
        return;
    }
    do_unknown_cmd(index, clients);
}

int check_cmds_nologin(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "HELP\r\n") == 0) {
        do_help_cmd(index, clients);
        return 1;
    }
    if (strcmp(buf, "QUIT\r\n") == 0) {
        do_quit_cmd(index, clients);
        return 1;
    }
    if (strcmp(buf, "\r\n") == 0) {
        do_unknown_cmd(index, clients);
        return 1;
    }
    return 0;
}
