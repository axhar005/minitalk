/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/13 17:55:57 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_sdata	*get_data()
{
	static t_sdata	data;

	return (&data);
}

void ft_draw_info()
{
    ft_putendl_fd("----------------------------------------", 1);
    ft_putendl_fd("|             Server Info              |", 1);
    ft_putendl_fd("----------------------------------------", 1);
    ft_putstr_fd("~ Server PID     : ", 1);
    ft_putnbr_fd(get_data()->server_pid, 1);
	ft_putchar_fd('\n', 1);
}

void ft_initialize_struct()
{
	get_data()->string = ft_sfree(get_data()->string);
	get_data()->bit_index = 0;
	get_data()->c = 0;
	get_data()->server_pid = getpid();
	get_data()->client_pid = 0;
	get_data()->string_index = 0;
	get_data()->string_len = 0;
	get_data()->start_recieve = false;
}

void add_char()
{
	if (!get_data()->string)
		get_data()->string = ft_calloc(get_data()->string_len + 1, sizeof(char));
	get_data()->string[get_data()->string_index] = get_data()->c;
	if (get_data()->string_index == (get_data()->string_len - 1))
	{
		kill(get_data()->client_pid, SIGUSR2);
		ft_putendl_fd("~ Message recieve :", 1);
		ft_putendl_fd(get_data()->string, 1);
   		ft_putchar_fd('\n', 1);
		ft_initialize_struct();
		return;
	}
	get_data()->string_index++;
}

void ft_receive_char(int signal)
{
	if (get_data()->bit_index <= 0)
		get_data()->bit_index = CHAR_SIZE;
	if (signal == SIGUSR1)
        signal = 0;
    else if (signal == SIGUSR2)
        signal = 1;
    get_data()->bit_index--;
	get_data()->c += (signal & 1) << get_data()->bit_index;
	if (get_data()->bit_index <= 0)
	{
		add_char();
		get_data()->c = 0;
	}
	if (get_data()->client_pid != 0)
		kill(get_data()->client_pid, SIGUSR1);
}

void ft_receive_len(int signal)
{
	static int len = 0;
	static int bit = 0;
	
	if (bit <= 0)
		bit = INT_SIZE;
	if (signal == SIGUSR1)
        signal = 0;
    else if (signal == SIGUSR2)
        signal = 1;
    bit--;
	len += (signal & 1) << bit;
	if (bit <= 0)
	{
		get_data()->string_len = len;
		len = 0;
		bit = 0;
		ft_putstr_fd("~ Message length : ", 1);
		ft_putnbr_fd(get_data()->string_len, 1);
   		ft_putchar_fd('\n', 1);
		kill(get_data()->client_pid, SIGUSR2);
		return;
	}
	kill(get_data()->client_pid, SIGUSR1);
}

void ft_receive_sort(int signal, siginfo_t *info, void *context)
{
	(void)*context;
	if (get_data()->client_pid == 0)
		get_data()->client_pid = info->si_pid;
	if (info->si_pid == get_data()->client_pid || info->si_pid == 0)
	{
		if (get_data()->start_recieve == false)
		{
			if (signal == SIGUSR1)
			{
				get_data()->start_recieve = true;
				kill(get_data()->client_pid, SIGUSR1);
			}
		}
		else if (get_data()->start_recieve == true)
		{
			if (get_data()->string_len <= 0)
				ft_receive_len(signal);
			else
				ft_receive_char(signal);
		}
	}
}

int	main(void)
{
	struct sigaction sig;
	
	ft_initialize_struct();
	ft_draw_info();
	sig.sa_sigaction = ft_receive_sort;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (true)
		pause();
	return (0);
}