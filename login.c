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
    memset(parsed, 0, strlen(buf));
    char *current = NULL;
    char *separator = strdup(" ");
    int i = 0;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    parsed[i] = NULL;
    if (my_arrlen(parsed) > 1) {
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
    char *current, *separator = strdup(" ");
    int i = 0;
    for (; (current = strtok_r(buf, separator, &buf)); i++) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
    }
    parsed[i] = NULL;
    if (clients[index].user == NULL) {
        write(clients[index].control_fd, NEEDACCOUNT, strlen(NEEDACCOUNT));
        return;
    }
    if (parsed[1])
        clients[index].pass = parsed[1];
    if ((strcasecmp(clients[index].user, "Anonymous") == 0)) {
        clients[index].connected = true;
        write(clients[index].control_fd, USERLOGGED, strlen(USERLOGGED));
    } else
        write(clients[index].control_fd, WRONGUSRMSG, strlen(WRONGUSRMSG));
}

int is_login_or_pass(char *buf)
{
    if (strncmp(buf, "USER", 4) == 0 || strncmp(buf, "PASS", 4) == 0) {
        return 1;
    }
    return 0;
}
