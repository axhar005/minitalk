/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/20 16:13:36 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// //type_size = 8bit/32bit
// void send(unsigned int octet, int pid, int type_size)
// {
//     int i;
    
//     (void)pid;
//     i = type_size;
//     while(i)
//     {
//         usleep(50);
//         i--;
//         if ((octet >> i & 1) == 1)
//         {
//             printf("1");
//             //kill(pid, SIGUSR2);
//         }
//         else
//         {
//             printf("0");
//             //kill(pid, SIGUSR1);
//         }
//     }
    
// }

// int main (int argc, char **argv)
// {
//     siginfo_t   info;
//     pid_t server_pid;
//     int i;
    
//     i = 0;
//     if (argc == 3)
//     {
//         server_pid = ft_atoi(argv[1]);
//         send('A', 687, 8);
//     }
// }