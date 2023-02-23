/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** cdup
*/

#include "my.h"

void do_cdup(int index, t_clients *clients)
{
    char *old_pwd = getcwd(NULL, 0);
    int val = chdir("..");
    if (val < 0) {
        write(clients[index].control_fd, ERRORCWD, strlen(ERRORCWD));
        return;
    }
    clients[index].old_pwd = old_pwd;
    clients[index].pwd = getcwd(NULL, 0);
    write(clients[index].control_fd, FILEACTION, strlen(FILEACTION));

}
