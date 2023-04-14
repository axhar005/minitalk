/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:07 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/13 21:48:59 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//Returns pointer to static t_sdata struct for efficient data management
static t_sdata	*data(void)
{
	static t_sdata	st;

	return (&st);
}

//This function revieve char bit from client
void	ft_receive_char(int signal)
{
	if (data()->bit_index <= 0)
		data()->bit_index = CHAR_SIZE;
	if (signal == SIGUSR1)
		signal = 0;
	else if (signal == SIGUSR2)
		signal = 1;
	data()->bit_index--;
	data()->c += (signal & 1) << data()->bit_index;
	if (data()->bit_index <= 0)
	{
		add_char(data());
		data()->c = 0;
	}
	if (data()->client_pid != 0)
		kill(data()->client_pid, SIGUSR1);
}

//This function revieve int bit from client
void	ft_receive_len(int signal)
{
	static int	len;
	static int	bit;

	len = 0;
	bit = 0;
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
		data()->string_len = len;
		len = 0;
		bit = 0;
		ft_putstr_fd("~ Message length : ", 1);
		ft_putnbr_fd(data()->string_len, 1);
		ft_putchar_fd('\n', 1);
		kill(data()->client_pid, SIGUSR2);
		return ;
	}
	kill(data()->client_pid, SIGUSR1);
}

//This function sorts signals and receives bit based on their type
void	ft_receive_sort(int signal, siginfo_t *info, void *context)
{
	(void)*context;
	if (data()->client_pid == 0)
		data()->client_pid = info->si_pid;
	if (info->si_pid == data()->client_pid || info->si_pid == 0)
	{
		if (data()->start_recieve == false)
		{
			if (signal == SIGUSR1)
			{
				data()->start_recieve = true;
				kill(data()->client_pid, SIGUSR1);
			}
		}
		else if (data()->start_recieve == true)
		{
			if (data()->string_len <= 0)
				ft_receive_len(signal);
			else
				ft_receive_char(signal);
		}
	}
}

int	main(void)
{
	struct sigaction	sig;

	init_server_struct(data());
	draw_server_info(data());
	sig.sa_sigaction = ft_receive_sort;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (true)
		pause();
	return (0);
}
