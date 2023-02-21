/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** main
*/

#include "my.h"

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    t_server *server = malloc(sizeof(t_server));
    server->port = my_getnbr(av[1]);
    server->serverpath = av[2];
    if (chdir(server->serverpath) == -1)
        exit (84);
    t_clients clients[100];
    for (int i = 0; i != 100; i++) {
        clients[i].control_fd = -1;
        clients[i].data_fd = -1;
        clients[i].original_data_fd = -1;
        clients[i].connected = false;
        clients[i].pass = NULL;
        clients[i].user = NULL;
    }
    int serverfd = create_server(server);
    loop_server(serverfd, clients, server);
}
