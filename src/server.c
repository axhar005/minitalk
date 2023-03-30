/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/29 21:26:59 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void draw(pid_t pid)
{
    ft_putendl_fd("----------------------------------------", 1);
    ft_putendl_fd("|              Server info             |", 1);
    ft_putendl_fd("----------------------------------------", 1);
    ft_putstr_fd("- PID : ", 1);
    ft_putnbr_fd(pid, 1);
    ft_putchar_fd('\n', 1);
}

void add_char(char **string, int *index, int len, char c)
{
    //ft_putchar_fd(c, 1);
    if (*string == NULL)
        *string = ft_calloc(len + 1, sizeof(char));
    string[0][*index] =  c;
    if (*index == len-1)
    {
        ft_putstr_fd(string[0], 1);
        *index = 0;
        return ;
    }
    *index += 1;
}

void ft_receive_len(int signal, int *length)
{
    static int bit;
    static int len;
    static int sig;
    
    if (bit <= 0)
        bit = INT_SIZE;
    if (signal == SIGUSR1)
        sig = 0;
    else if (signal == SIGUSR2)
        sig = 1;
    bit--;
	len += (sig & 1) << bit;
    if (bit == 0)
    {
        *length = len;
        bit = 0;
        len = 0;
    }
    
}

void ft_receive(int signal, siginfo_t *info, void *context)
{
    (void)context;
    static int bit = 0;
    static int len = 0;
    static int index = 0;
    static char *string = NULL;
    static char c;
    int pid;
    
    if (len <= 0)
    {
        ft_receive_len(signal, &len);
    }
    else
    {
        //ft_putnbr_fd(len, 1);
        if (bit <= 0)
            bit = CHAR_SIZE;
        if (signal == SIGUSR1)
            signal = 0;
        else if (signal == SIGUSR2)
            signal = 1;
        bit--;
        c += (signal & 1) << bit;
        if (bit == 0)
        {
            //ft_putchar_fd(c, 1);
            add_char(&string, &index, len, c);
            bit = CHAR_SIZE;
            c = 0;
            pid = info->si_pid;
        }
    }
}

int main(void)
{
    pid_t pid;
    struct sigaction sig;

    pid = getpid();
    draw(pid);
    sig.sa_sigaction = ft_receive;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
    while(1)
        pause();
    return(0);
}