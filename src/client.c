/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/01 01:39:17 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_cdata *get_data()
{
    static t_cdata data;
    return(&data);
}

//type_size = 8bit/32bit
void ft_send(unsigned int octet, int type_size)
{
    int bit_index;
    
    bit_index = type_size;
    while(bit_index)
    {
        usleep(10);
        bit_index--;
        if ((octet >> bit_index & 1) == 1)
        {
            kill(get_data()->server_pid, SIGUSR2);
        }
        else
        {
            kill(get_data()->server_pid, SIGUSR1);
        }
    }
}

void ft_receive(int signal, siginfo_t *info, void *context)
{
    (void)*context;
    (void)*info;
    if (signal == SIGUSR1)
    {
        ft_putstr_fd("allo", 1);
        ft_send(get_data()->string[get_data()->index], CHAR_SIZE);
        get_data()->index += 1;
    }
}

int main (int argc, char **argv)
{
    struct sigaction sig;
    int i;
    
    i = 0;
    if (argc == 3)
    {
        get_data()->index = 0;
        get_data()->string = argv[2];
        get_data()->length = ft_strlen(argv[2]);
        get_data()->server_pid = ft_atoi(argv[1]);
        sig.sa_sigaction = ft_receive;
        sig.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &sig, NULL);
        ft_send(get_data()->length, INT_SIZE);
        usleep(1234);
        ft_send(get_data()->string[get_data()->index], CHAR_SIZE);
    }
    while(1)
        pause();
    return (0);
}