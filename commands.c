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
    buf[strlen(buf) - 2] = '\0';
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current, *separator = strdup(" ");
    int i = 0, fd;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    if (clients[index].data_fd == -1 && clients[index].original_data_fd == -1) {
        write(clients[index].control_fd, NODATA, strlen(NODATA));
        return;
    }
    if (parsed[1] && (fd = open(parsed[1], O_RDONLY)) == -1) {
        write(clients[index].control_fd, "550 Failed to open file.\n\r", 26);
        return;
    }
    send_file_to_data(index, clients, parsed[1], fd);
}

void send_file_to_data(int index, t_clients *clients, char *path, int fd)
{
    if (!path) {
        write(clients[index].control_fd, "550 Failed to open file.\n\r", 26);
        return;
    }
    char *buf = malloc(sizeof(char) * 1024);
    memset(buf, 0, 1024);
    ssize_t byte = 0;
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    while (1) {
        byte = read(fd, buf, sizeof(buf));
        if (byte == -1 || byte == 0) {
            break;
        }
        write(clients[index].data_fd, buf, strlen(buf));
        memset(buf, 0, 1024);
    }
    close(fd);
    free(buf);
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
    clear_client_data(index, clients);
}
