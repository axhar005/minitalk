/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/05/02 20:51:58 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//Returns pointer to static t_cdata struct for efficient data management
static t_cdata	*data(void)
{
	static t_cdata	st;

	return (&st);
}

//This function send int bit to the server
void	ft_send_int(void)
{
	if (data()->bit_index <= 0)
		data()->bit_index = INT_SIZE;
	data()->bit_index--;
	if ((data()->string_len >> data()->bit_index & 1) == 1)
		kill(data()->server_pid, SIGUSR2);
	else
		kill(data()->server_pid, SIGUSR1);
}

//This function send char bit to the server
void	ft_send_char(void)
{
	if (data()->bit_index <= 0)
		data()->bit_index = CHAR_SIZE;
	data()->bit_index--;
	if ((data()->string[data()->string_index] >> data()->bit_index & 1) == 1)
		kill(data()->server_pid, SIGUSR2);
	else
		kill(data()->server_pid, SIGUSR1);
	if (data()->bit_index <= 0)
		data()->string_index++;
}

//This function sorts signals and sends bit based on their type
void	ft_receive_sort(int signal, siginfo_t *info, void *context)
{
	(void)*context;
	data()->tick = 0;
	if (info->si_pid == data()->server_pid || info->si_pid == 0)
	{
		if (signal == SIGUSR1)
		{
			if (data()->length_send == false)
				ft_send_int();
			else
				ft_send_char();
		}
		else if (signal == SIGUSR2)
		{
			if (data()->length_send == false)
			{
				data()->length_send = true;
				ft_send_char();
			}
			else
			{
				ft_putendl_fd("\033[32;1mMessage sended !", 1);
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;

	ft_initialize_cstruct(data(), argv);
	data()->tick = 0;
	if (argc == 3)
	{
		sig.sa_sigaction = ft_receive_sort;
		sig.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		if (data()->string[0] != '\0')
			kill(data()->server_pid, SIGUSR1);
	}
	while (true)
	{
		if (data()->tick == 1000)
		{
			ft_putendl_fd("\033[31;1mFail to send data !", 1);
			exit(EXIT_FAILURE);
		}
		usleep(10);
		data()->tick++;
	}
	return (0);
}
