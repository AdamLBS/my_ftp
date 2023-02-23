/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** cwd
*/

#include "my.h"

void do_cwd_cmd(int index, t_clients *clients, char *buf)
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
    if (!parsed[1]) {
        write(clients[index].control_fd, ERRORCWD, strlen(ERRORCWD));
        return;
    }
    do_change_directory(parsed[1], index, clients);
}

void do_change_directory(char *dir, int index, t_clients *clients)
{
    char *old_pwd = getcwd(NULL, 0);
    int val = chdir(dir);
    if (val < 0) {
        write(clients[index].control_fd, ERRORCWD, strlen(ERRORCWD));
        return;
    }
    clients[index].old_pwd = old_pwd;
    clients[index].pwd = dir;
    write(clients[index].control_fd, FILEACTION, strlen(FILEACTION));
}
