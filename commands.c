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

    int port1 = port/256;
    int port2 = port % 256;
    my_itoa(port1, portStr1);
    my_itoa(port2, portStr2);
    write(fd, "227 Entering Passive Mode ", 27);
    write(fd, "(", 1);
    write(fd, adress, strlen(adress));
    write(fd, ",", 1);
    write(fd, portStr1, strlen(portStr1));
    write(fd, ",", 1);
    write(fd, portStr2, strlen(portStr2));
    write(fd, ")\n", 2);
}

void do_retr_cmd(int index, t_clients *clients, char *buf)
{
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current;
    char *separator = strdup(" ");
    int i = 0;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    if (clients[index].data_fd == -1 && clients[index].original_data_fd == -1) {
        write(clients[index].control_fd, "425 Use PORT or PASV first.\n", 29);
        return;
    }
    if (parsed[1] && open(parsed[1], O_RDONLY) == -1) {
        write(clients[index].control_fd, "550 Failed to open file.\n", 26);
        return;
    }
    if (parsed[1])
        puts(parsed[1]);
}