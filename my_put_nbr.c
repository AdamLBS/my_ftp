/*
** EPITECH PROJECT, 2021
** my_put_nbr
** File description:
** my_put_nbr.c
*/

#include "my.h"

void my_put_nbr(int nb)
{
    int aux = 0;

    if (nb < 0 && aux == 0) {
        my_putchar('-');
        my_put_nbr(nb * -1);
    } else {
        if (nb >= 10) {
            my_put_nbr(nb / 10);
            my_put_nbr(nb % 10);
        } else {
            my_putchar(nb + '0');
        }
    }
}
