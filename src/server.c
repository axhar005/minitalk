/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/01 01:42:19 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_sdata *get_data()
{
    static t_sdata data;
    return(&data);
}

void draw()
{
    ft_putendl_fd("----------------------------------------", 1);
    ft_putendl_fd("|              Server info             |", 1);
    ft_putendl_fd("----------------------------------------", 1);
    ft_putstr_fd("- PID : ", 1);
    ft_putnbr_fd(get_data()->server_pid, 1);
    ft_putchar_fd('\n', 1);
}

void add_char()
{
    if (get_data()->string == NULL)
        get_data()->string = ft_calloc(get_data()->length + 1, sizeof(char));
    get_data()->string[get_data()->index] =  get_data()->c;
    if (get_data()->index == get_data()->length-1)
    {
        ft_putustr_fd(get_data()->string, 1);
        ft_putchar_fd('\n', 1);
        get_data()->string = ft_sfree(get_data()->string);
        get_data()->index = 0;
        get_data()->length = 0;
        return ;
    }
    get_data()->index += 1;
}

void ft_receive_int(int signal)
{
    static int len = 0;
    
    if (get_data()->bit_index <= 0)
        get_data()->bit_index = INT_SIZE;
    if (signal == SIGUSR1)
        signal = 0;
    else if (signal == SIGUSR2)
        signal = 1;
    get_data()->bit_index--;
	len += (signal & 1) << get_data()->bit_index;
    if (get_data()->bit_index == 0)
    {
        get_data()->length = len;
        len = 0;
        //kill(get_data()->client_pid, SIGUSR1);
        ft_putnbr_fd(get_data()->length, 1);
        ft_putchar_fd('\n', 1);
    }
    
}

//Get signal and transform in char
void ft_receive_char(int signal)
{   
    if (get_data()->bit_index <= 0)
        get_data()->bit_index = CHAR_SIZE;
    if (signal == SIGUSR1)
    {
        signal = 0;
       // ft_putchar_fd('0', 1);
    }
    else if (signal == SIGUSR2)
    {
        signal = 1;
    }
    get_data()->bit_index--;
    get_data()->c += (signal & 1) << get_data()->bit_index;
    ft_putchar_fd(get_data()->c, 1);
    if (get_data()->bit_index == 0)
    {
        add_char();
        get_data()->c = 0;
        //kill(get_data()->client_pid, SIGUSR1);
    }
}

//Receive signal and dispatch for int or char
void ft_receive(int signal, siginfo_t *info, void *context)
{
    (void)context;
    int opid;
    if (get_data()->length <= 0)
    {
        ft_receive_int(signal);
    }
    else
    {
        ft_receive_char(signal);
        opid = info->si_pid;
    }
}

int main(void)
{
    struct sigaction sig;

    get_data()->string = NULL;
    get_data()->bit_index = 0;
    get_data()->index = 0;
    get_data()->length = 0;
    get_data()->c = 0;
    get_data()->server_pid = getpid();
    draw();
    sig.sa_sigaction = ft_receive;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
    while(1)
        pause();
    return(0);
}