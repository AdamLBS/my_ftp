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
    int datalen = sizeof(adress);
    getsockname(clients[index].control_fd, (struct sockaddr *)&adress,
    (socklen_t*) (&datalen) );
    struct in_addr ipaddr = adress.sin_addr;
    char **parsed = split_args(buf);
    if (my_arrlen(parsed) != 6) {
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        return;
    }
    inet_ntop(AF_INET, &ipaddr, get_client_ip(parsed), INET_ADDRSTRLEN);
    int port = get_port(parsed[4], parsed[5]);
    data_addr.sin_port = htons(port);
    data_addr.sin_family = AF_INET;
    clients[index].data_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (check_port_connection(clients, index, data_addr, get_client_ip(parsed)))
        return;
    write(clients[index].control_fd, PORTOKAY, strlen(PORTOKAY));
    clients[index].original_data_fd = clients[index].data_fd;
}

char *get_client_ip(char **parsed)
{
    char *full_val = malloc(sizeof(char) * 17);
    int max = 4;
    for (int i = 0; i != max ; i++) {
        strcat(full_val, parsed[i]);
        int len = strlen(full_val);
        if (i + 1 != 4) {
            full_val[len] = '.';
            full_val[len + 1] = '\0';
        }
    }
    write(1, full_val, strlen(full_val));
    return full_val;
}

int get_port(char *port1, char *port2)
{
    int fullval = 0;
    int port1_val = my_getnbr(port1);
    int port2_val = my_getnbr(port2);
    fullval = (port1_val * 256) + port2_val;
    return fullval;
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
    char **parsed2 = malloc(sizeof(char *) * strlen(buf));
    char *current, *current2;
    char *buf2 = strdup(buf);
    char *separator2 = strdup(",");
    int i = 0, j = 0;
    while (buf2[0] != '\0' && buf2[0] < 48 || buf2[0] > 57) {
        buf2++;
    }
    while ((current2 = strtok_r(buf2, separator2, &buf2))) {
        char *new_string = strdup(current2);
        parsed2[j] = new_string;
        j++;
    }
    return parsed2;
}
