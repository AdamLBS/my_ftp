/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** main
*/

#include "my.h"

int main(void)
{
    t_clients clients[100];
    for (int i = 0; i != 100; i++) {
        clients[i].control_fd = -1;
        clients[i].data_fd = -1;
        clients[i].original_data_fd = -1;
        clients[i].connected = false;
        clients[i].pass = NULL;
        clients[i].user = NULL;
    }
    int server = create_server();
    loop_server(server, clients);
}


