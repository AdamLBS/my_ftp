/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** login
*/

#include "my.h"

void do_user_cmd(int index, t_clients *clients, char *buf)
{
    buf[strlen(buf) - 2] = '\0';
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current;
    char *separator = strdup(" ");
    int i = 0;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    if (parsed[1]) {
        clients[index].user = parsed[1];
        char *msg = strdup("331 User name okay, need password.\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
    }
    return;
}

void do_pass_cmd(int index, t_clients *clients, char *buf)
{
    buf[strlen(buf) - 2] = '\0';
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current;
    char *separator = strdup(" ");
    int i = 0;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    if (clients[index].user == NULL) {
        char *msg = strdup("503 Login with USER first.\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return;
    }
    if (parsed[1])
        clients[index].pass = parsed[1];
    if (strcasecmp(clients[index].user, "Anonymous") == 0 && clients[index].pass == NULL) {
        clients[index].connected = true;
        char *msg = strdup("230 User logged in, proceed.\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
    }
    return;
}

int is_login_or_pass(char *buf)
{
    if (strncmp(buf, "USER", 4) == 0 || strncmp(buf, "PASS", 4) == 0) {
        return 1;
    }
    return 0;
}