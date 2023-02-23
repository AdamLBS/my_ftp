/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** check_cmds
*/

#include "my.h"

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
    if (strncmp(buf, "LIST", 4) == 0) {
        do_list(index, clients);
        return;
    }
    if (strncmp(buf, "CWD", 3) == 0) {
        do_cwd_cmd(index, clients, buf);
        return;
    }
    check_cmds3(index, clients, buf);
}

void check_cmds3(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "CDUP\r\n") == 0) {
        do_cdup(index, clients);
        return;
    }
    if (clients[index].connected)
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
