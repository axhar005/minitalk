/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/29 22:13:03 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//type_size = 8bit/32bit
void ft_send(unsigned int octet, int pid, int type_size)
{
    int i;
    
    (void)pid;
    i = type_size;
    while(i)
    {
        usleep(100);
        i--;
        if ((octet >> i & 1) == 1)
        {
            kill(pid, SIGUSR2);
        }
        else
        {
            kill(pid, SIGUSR1);
        }
    }
    
}

int main (int argc, char **argv)
{
   // siginfo_t   info;
    pid_t server_pid;
    int len;
    int i;

    i = 0;
    if (argc == 3)
    {
        len = ft_strlen(argv[2]);
        server_pid = ft_atoi(argv[1]);
        ft_send(len, server_pid, INT_SIZE);
        while(argv[2][i])
        {
            ft_send(argv[2][i], server_pid, CHAR_SIZE);
            i++;
        }
    }
}