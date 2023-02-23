/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** delete
*/

#include "my.h"

void do_delete_cmd(int index, t_clients *clients, char *buf)
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
    if (!parsed[1]) {
        write(clients[index].control_fd, ERRORDEL, strlen(ERRORDEL));
        return;
    }
    do_delete(parsed[1], index, clients);
}

void do_delete(char *file, int index, t_clients *clients)
{
    if (remove(file) < 0) {
        write(clients[index].control_fd, "501 Error.\r\n", 12);
        return;
    }
    write(clients[index].control_fd, FILEACTION, strlen(FILEACTION));
}
