/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/30 20:42:13 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_var g_var;

void draw()
{
    ft_putendl_fd("----------------------------------------", 1);
    ft_putendl_fd("|              Server info             |", 1);
    ft_putendl_fd("----------------------------------------", 1);
    ft_putstr_fd("- PID : ", 1);
    ft_putnbr_fd(g_var.pid, 1);
    ft_putchar_fd('\n', 1);
}

void add_char()
{
    //ft_putchar_fd(g_var.c, 1);
    if (g_var.string == NULL)
        g_var.string = ft_calloc(g_var.length + 1, sizeof(char));
    g_var.string[g_var.index] =  g_var.c;
    if (g_var.index == g_var.length-1)
    {
        ft_putustr_fd(g_var.string, 1);
        ft_putchar_fd('\n', 1);
        g_var.string = ft_sfree(g_var.string);
        g_var.index = 0;
        g_var.length = 0;
        return ;
    }
    g_var.index += 1;
}

void ft_receive_int(int signal)
{
    static int len = 0;
    
    if (g_var.bit_index <= 0)
        g_var.bit_index = INT_SIZE;
    if (signal == SIGUSR1)
        signal = 0;
    else if (signal == SIGUSR2)
        signal = 1;
    g_var.bit_index--;
	len += (signal & 1) << g_var.bit_index;
    if (g_var.bit_index == 0)
    {
        g_var.length = len;
        len = 0;
    }
    
}

void ft_receive_char(int signal)
{   
    //ft_putnbr_fd(g_var.len, 1);
    if (g_var.bit_index <= 0)
        g_var.bit_index = CHAR_SIZE;
    if (signal == SIGUSR1)
        signal = 0;
    else if (signal == SIGUSR2)
        signal = 1;
    g_var.bit_index--;
    g_var.c += (signal & 1) << g_var.bit_index;
    if (g_var.bit_index == 0)
    {
        add_char();
        g_var.c = 0;
    }
}

void ft_receive(int signal, siginfo_t *info, void *context)
{
    (void)context;
    int opid;
    if (g_var.length <= 0)
    {
        ft_receive_int(signal);
    }
    else
    {
        // ft_putnbr_fd(g_var.length, 1);
        ft_receive_char(signal);
        opid = info->si_pid;
    }
}

int main(void)
{
    struct sigaction sig;

    g_var.string = NULL;
    g_var.bit_index = 0;
    g_var.index = 0;
    g_var.length = 0;
    g_var.pid = getpid();
    draw();
    sig.sa_sigaction = ft_receive;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
    while(1)
        pause();
    return(0);
}