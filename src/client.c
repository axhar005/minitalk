/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/16 16:44:11 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main (int argc, char *argv)
{
    int server_pid;
    
    if (argc == 2)
    {
        server_pid = ft_atoi(argv[1]);
    }
}