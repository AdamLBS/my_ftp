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
    create_buffer(index, clients);
    char buf[1000] = {0};
    int val = read(clients[index].control_fd, buf, 1000);
    if (val == 0 && clients[index].control_fd) {
        close(clients[index].control_fd);
        clients[index].control_fd = -1;
    }
    strcat(clients[index].buffer, buf);
    if (!is_buffer_ended(index, clients))
        return;
    if (check_cmds_nologin(index, clients, clients[index].buffer))
        return;
    if (strcmp(clients[index].buffer, "LOGOUT\r\n") == 0 )
        do_logout(index, clients);
    if (is_login_or_pass(clients[index].buffer) == 0 &&
    !is_client_logged_in(index, clients))
        clients[index].buffer[0] = '\0';
    check_cmds(index, clients, clients[index].buffer);
}

int is_buffer_ended(int index, t_clients *clients)
{
    int len = strlen(clients[index].buffer);
    if (len < 2)
        return 0;
    if (clients[index].buffer[len - 1] == '\0' ||
    clients[index].buffer[len - 2] == '\0')
        return 0;
    if (clients[index].buffer[len - 1] != '\n' ||
    clients[index].buffer[len - 2] != '\r')
        return 0;
    return 1;
}
