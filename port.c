/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** port
*/

#include "my.h"

void do_port_cmd(int index, t_clients *clients, char *buf)
{
    struct sockaddr_in data_addr;
    int datalen = sizeof(data_addr);
    char **parsed = split_args(buf);
    clear_client_data(index, clients);
    char *ip = get_client_ip(parsed);
    if (my_arrlen(parsed) != 6) {
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        return;
    }
    clients[index].activ_ip = strdup(ip);
    clients[index].activ_port = get_port(parsed[4], parsed[5]);
    clients[index].pasv = false;
    write(clients[index].control_fd, PORTOKAY, strlen(PORTOKAY));
    free_port_val(ip, parsed);
}

char *get_client_ip(char **parsed)
{
    char *full_val = malloc(sizeof(char) * 17);
    memset(full_val, 0, 17);
    int max = 4;
    for (int i = 0; i != max ; i++) {
        strcat(full_val, parsed[i]);
        if ((i + 1 != max))
            strcat(full_val, ".");
    }
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
        clients[index].original_data_fd = -1;
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        return 1;
    }
    if (connect(clients[index].data_fd, (struct sockaddr*)&data_addr,
    sizeof(data_addr)) < 0) {
        write(clients[index].control_fd, PORTERR, strlen(PORTERR));
        close(clients[index].data_fd);
        clients[index].data_fd = -1;
        clients[index].original_data_fd = -1;
        return 1;
    };
    return 0;
}

char **split_args(char *buf)
{
    char **parsed2 = malloc(sizeof(char *) * strlen(buf) + 1);
    buf[strlen(buf) - 2] = '\0';
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
    parsed2[j] = NULL;
    return parsed2;
}
