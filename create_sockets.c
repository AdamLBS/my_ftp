/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** create_sockets
*/

#include "my.h"

int create_server(void)
{
    struct sockaddr_in adress;
    adress.sin_port = htons(4242);
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        exit (84);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &(int){1}, sizeof(int));
    int bindval = bind(sockfd, (struct sockaddr *)&adress, sizeof(struct sockaddr_in));
    if (bindval != 0)
        exit (84);
    int listen_return = listen(sockfd, 100);
    if (listen_return != 0)
        exit (84);
    return sockfd;
}