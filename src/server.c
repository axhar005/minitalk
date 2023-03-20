/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/20 16:28:00 by oboucher         ###   ########.fr       */
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

void sigtostr(int sig, siginfo_t *info, void *other)
{
    (void)other;
    
     
}

int main(void)
{
    pid_t pid;
    struct sigaction sig;

    pid = getpid();
    draw(pid);
    sig.sa_sigaction = sigtostr;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
    while(1)
        pause();
    return(0);
}