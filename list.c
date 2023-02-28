/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** list
*/

#include "my.h"

void do_list(int index, t_clients *clients)
{
    if (does_client_has_data(index, clients) == 0)
        return;
    DIR *dir;
    struct dirent *list;
    char *dirlist = malloc(sizeof(char) * 10000);
    memset(dirlist, 0, 10000);
    dir = opendir(getcwd(NULL, 0));
    if (!dir) {
        char *msg = strdup("550 Error while opening directory\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return;
    }
    while ((list = readdir(dir))) {
        char tmp[100] = {0};
        snprintf(tmp, sizeof(tmp), "%s\r\n", list->d_name);
        strcat(dirlist, tmp);
    }
    closedir(dir);
    send_list_data(dirlist, index, clients);
    clear_client_data(index, clients);
}

void do_list_with_params(int index, t_clients *clients, char *buf)
{
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
    DIR *dir;
    struct dirent *list;
    char *dirlist = malloc(sizeof(char) * 10000);
    memset(dirlist, 0, 10000);
    dir = opendir(val);
    if (!dir) {
        char *msg = strdup("550 Error while opening directory\r\n");
        write(clients[index].control_fd, msg, strlen(msg));
        return;
    }
    while ((list = readdir(dir))) {
        char tmp[100] = {0};
        snprintf(tmp, sizeof(tmp), "%s\r\n", list->d_name);
        strcat(dirlist, tmp);
    }
    closedir(dir);
    send_list_data(dirlist, index, clients);
    clear_client_data(index, clients);
}

void send_list_data(char *dirlist, int index, t_clients *clients)
{
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    write(clients[index].data_fd, dirlist, strlen(dirlist));
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
}
