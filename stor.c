/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** stor
*/

#include "my.h"

void do_stor_cmd(int index, t_clients *clients, char *buf)
{
    buf[strlen(buf) - 2] = '\0';
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current, *separator = strdup(" ");
    int i = 0, fd;
    for (; (current = strtok_r(buf, separator, &buf)); i++) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
    }
    if (clients[index].data_fd == -1 && clients[index].original_data_fd == -1
    && clients[index].pasv) {
        write(clients[index].control_fd, NODATA, strlen(NODATA));
        return;
    }
    if (!parsed[1]) {
        write(clients[index].control_fd, ERRORDEL, strlen(ERRORDEL));
        return;
    }
    accept_data(index, clients);
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    upload_data_to_file(index, clients, parsed[1]);
}

void upload_data_to_file(int index, t_clients *clients, char *path)
{
    FILE *fd = fopen(path, "w");
    clients[index].check_read = true;
    clients[index].readfd = fd;
}
