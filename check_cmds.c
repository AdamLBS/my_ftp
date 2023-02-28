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
        return clear_buffer(index, clients);
    }
    if (strcmp(buf, "NOOP\r\n") == 0) {
        do_noop(index, clients);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "RETR", 4) == 0) {
        do_retr_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "USER", 4) == 0) {
        do_user_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    check_cmds2(index, clients, buf);
}

void check_cmds2(int index, t_clients *clients, char *buf)
{
    if (strncmp(buf, "PASS", 4) == 0) {
        do_pass_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    if (strcmp(buf, "PWD\r\n") == 0) {
        do_pwd(index, clients);
        return clear_buffer(index, clients);
    }
    if (strcmp(buf, "LIST\r\n") == 0) {
        do_list(index, clients);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "CWD", 3) == 0) {
        do_cwd_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    check_cmds3(index, clients, buf);
}

void check_cmds3(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "CDUP\r\n") == 0) {
        do_cdup(index, clients);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "DELE", 4) == 0) {
        do_delete_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "STOR", 4) == 0) {
        do_stor_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    if (strncmp(buf, "LIST", 4) == 0) {
        do_list_with_params(index, clients, buf);
        return clear_buffer(index, clients);
    }
    check_cmds4(index, clients, buf);
}

void check_cmds4(int index, t_clients *clients, char *buf)
{
    if (strncmp(buf, "PORT", 4) == 0) {
        do_port_cmd(index, clients, buf);
        return clear_buffer(index, clients);
    }
    if (clients[index].connected)
        do_unknown_cmd(index, clients);
}

int check_cmds_nologin(int index, t_clients *clients, char *buf)
{
    if (strcmp(buf, "HELP\r\n") == 0) {
        do_help_cmd(index, clients);
        free(clients[index].buffer);
        clients[index].buffer = NULL;
        return 1;
    }
    if (strcmp(buf, "QUIT\r\n") == 0) {
        do_quit_cmd(index, clients);
        free(clients[index].buffer);
        clients[index].buffer = NULL;
        return 1;
    }
    if (strcmp(buf, "\r\n") == 0) {
        do_unknown_cmd(index, clients);
        free(clients[index].buffer);
        clients[index].buffer = NULL;
        return 1;
    }
    return 0;
}
