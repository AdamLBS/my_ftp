/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** list
*/

#include "my.h"

void do_list(int index, t_clients *clients)
{
    accept_data(index, clients);
    if (does_client_has_data(index, clients) == 0)
        return;
    FILE *fd = popen("ls -l --time-style='+'", "r");
    if (!fd) {
        char *msg = strdup("550 Error while opening directory\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return;
    }
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    char buf2[BUFSIZ];
    my_put_nbr(clients[index].data_fd);
    while (fgets(buf2, BUFSIZ, fd) > 0) {
        write(clients[index].data_fd, buf2, strlen(buf2));
        memset(buf2, 0, BUFSIZ);
    }
    fclose(fd);
    send_list_data("", index, clients);
    clear_client_data(index, clients);
}

void do_list_with_params(int index, t_clients *clients, char *buf)
{
    accept_data(index, clients);
    if (does_client_has_data(index, clients) == 0)
        return;
    buf[strlen(buf) - 2] = '\0';
    char **parsed = malloc(sizeof(char *) * strlen(buf));
    char *current, *separator = strdup(" ");
    int i = 0;
    while ((current = strtok_r(buf, separator, &buf))) {
        char *new_string = strdup(current);
        parsed[i] = new_string;
        i++;
    }
    if (!parsed[1])
        return do_list(index, clients);
    return exec_list_params(index, clients, parsed[1]);
}

void exec_list_params(int index, t_clients *clients, char *val)
{
    accept_data(index, clients);
    char *buf = malloc(sizeof(char) * 10000);
    sprintf(buf, "ls -l %s --time-style='+'", val);
    FILE *fd = popen(buf, "r");
    if (!fd) {
        char *msg = strdup("550 Error while opening directory\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return;
    }
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    char buf2[BUFSIZ];
    while (fgets(buf2, BUFSIZ, fd) > 0) {
        write(clients[index].data_fd, buf2, strlen(buf2));
        memset(buf2, 0, BUFSIZ);
    }
    free(buf);
    fclose(fd);
    send_list_data("", index, clients);
    clear_client_data(index, clients);
}

void send_list_data(char *dirlist, int index, t_clients *clients)
{
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
}
