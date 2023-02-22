/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** pwd
*/

#include "my.h"

void do_pwd(int index, t_clients *clients)
{
    chdir(clients[index].pwd);
    char *old_pwd = getcwd(NULL, 0);
    write(clients[index].control_fd, "257 ", 4);
    write(clients[index].control_fd, old_pwd, strlen(old_pwd));
    write(clients[index].control_fd, " created.\r\n", 11);
}
