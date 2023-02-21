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

void send_list_data(char *dirlist, int index, t_clients *clients)
{
    write(clients[index].control_fd, FILEOKAY, strlen(FILEOKAY));
    write(clients[index].data_fd, dirlist, strlen(dirlist));
    write(clients[index].control_fd, CLOSEDATA, strlen(CLOSEDATA));
}
