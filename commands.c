/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** commands
*/

#include "my.h"

void send_pasv_info(char *adress, int port, int fd)
{
    for (int i = 0; adress[i]; i++) {
        if (adress[i] == '.')
            adress[i] = ',';
    }
    char *portStr1 = malloc(sizeof(char) * 10);
    char *portStr2 = malloc(sizeof(char) * 10);
    int port1 = port / 256;
    int port2 = port % 256;
    my_itoa(port1, portStr1);
    my_itoa(port2, portStr2);
    write(fd, "227 Entering Passive Mode ", 26);
    write(fd, "(", 1);
    write(fd, adress, strlen(adress));
    write(fd, ",", 1);
    write(fd, portStr1, strlen(portStr1));
    write(fd, ",", 1);
    write(fd, portStr2, strlen(portStr2));
    write(fd, ")\r\n", 3);
    free(portStr1);
    free(portStr2);
}

void do_retr_cmd(int index, t_clients *clients, char *buf)
{
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    memset(parsed, 0, strlen(buf));
    buf[strlen(buf) - 2] = '\0';
    char *current, *separator = strdup(" ");
    FILE *fd;
    for (int i = 0; (current = strtok_r(buf, separator, &buf)); i++) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
    }
    if (clients[index].data_fd == -1 && clients[index].original_data_fd == -1
    && clients[index].pasv) {
        write(clients[index].control_fd, NODATA, strlen(NODATA));
        return;
    }
    if (parsed[1] && (fd = fopen(parsed[1],"rb")) == NULL) {
        write(clients[index].control_fd, "550 Failed to open file.\n\r", 26);
        return;
    }
    accept_data(index, clients);
    send_file_to_data(index, clients, parsed[1], fd);
}

void send_file_to_data(int index, t_clients *clients, char *path, FILE *fd)
{
    struct stat info;
    stat(path, &info);
    my_put_nbr(info.st_size);
    char *buf = malloc(sizeof(char) * info.st_size);
    memset(buf, 0, info.st_size);
    int size = 0;
    int bytes_read = 0;
    fread(buf + size, sizeof(char), info.st_size, fd);
    fclose(fd);
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    write(clients[index].data_fd, buf, info.st_size);
    free(buf);
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
    clear_client_data(index, clients);
}
