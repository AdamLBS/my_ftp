/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** main
*/

#include "my.h"

int main(int ac, char **av)
{
    if (help_message(ac, av))
        return 0;
    if (ac != 3)
        return 84;
    t_server *server = malloc(sizeof(t_server));
    server->port = my_getnbr(av[1]);
    server->serverpath = av[2];
    if (chdir(server->serverpath) == -1)
        exit (84);
    t_clients clients[100];
    initialize_clients(clients, server);
    int serverfd = create_server(server);
    loop_server(serverfd, clients, server);
}

int help_message(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        struct stat info;
        stat("helpmsg.txt", &info);
        char *buf = malloc(sizeof(char) * info.st_size);
        int fd = open("helpmsg.txt", O_RDONLY);
        read(fd, buf, info.st_size);
        write(1, buf, strlen(buf));
        return 1;
    }
    return 0;
}

void initialize_clients(t_clients *clients, t_server *server)
{
    for (int i = 0; i != 100; i++) {
        clients[i].control_fd = -1;
        clients[i].data_fd = -1;
        clients[i].original_data_fd = -1;
        clients[i].connected = false;
        clients[i].pass = NULL;
        clients[i].user = NULL;
        clients[i].pwd = server->serverpath;
    }
}