/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** port
*/

#include "my.h"

void do_port_cmd(int index, t_clients *clients, char *buf)
{
    struct sockaddr_in adress, data_addr;
    char str[INET_ADDRSTRLEN];
    int datalen = sizeof(adress);
    getsockname(clients[index].control_fd, (struct sockaddr *)&adress,
    (socklen_t*) (&datalen) );
    struct in_addr ipaddr = adress.sin_addr;
    inet_ntop(AF_INET, &ipaddr, str, INET_ADDRSTRLEN);
    char **parsed = split_args(buf);
    if (!parsed[1]) {
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        return;
    }
    int port = my_getnbr(parsed[1]);
    data_addr.sin_port = htons(port);
    data_addr.sin_family = AF_INET;
    clients[index].data_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (check_port_connection(clients, index, data_addr, str))
        return;
    write(clients[index].control_fd, PORTOKAY, strlen(PORTOKAY));
    clients[index].original_data_fd = clients[index].data_fd;
}

int check_port_connection(t_clients *clients, int index,
struct sockaddr_in data_addr, char *str)
{
    if (inet_pton(AF_INET, str, &data_addr.sin_addr) < 0) {
        close(clients[index].data_fd);
        clients[index].data_fd = -1;
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        return 1;
    }
    if (connect(clients[index].data_fd, (struct sockaddr*)&data_addr,
    sizeof(data_addr)) < 0) {
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        close(clients[index].data_fd);
        clients[index].data_fd = -1;
        return 1;
    };
    return 0;
}

char **split_args(char *buf)
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
    return parsed;
}
