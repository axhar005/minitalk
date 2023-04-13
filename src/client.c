/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:17:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/13 17:01:41 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_cdata	*get_data()
{
	static t_cdata	data;

	return (&data);
}

void	ft_send_int(void)
{
	if (get_data()->bit_index <= 0)
		get_data()->bit_index = INT_SIZE;
	get_data()->bit_index--;
	if ((get_data()->string_len >> get_data()->bit_index & 1) == 1)
		kill(get_data()->server_pid, SIGUSR2);
	else
		kill(get_data()->server_pid, SIGUSR1);
}

void	ft_send_char(void)
{
	if (get_data()->bit_index <= 0)
		get_data()->bit_index = CHAR_SIZE;
	get_data()->bit_index--;
	if ((get_data()->string[get_data()->string_index] >> get_data()->bit_index & 1) == 1)
		kill(get_data()->server_pid, SIGUSR2);
	else
		kill(get_data()->server_pid, SIGUSR1);
	if (get_data()->bit_index <= 0)
		get_data()->string_index++;
}

void	ft_receive_sort(int signal, siginfo_t *info, void *context)
{
	(void)*context;
	if (info->si_pid == get_data()->server_pid || info->si_pid == 0)
	{
		if (signal == SIGUSR1)
		{
			if (get_data()->length_send == false)
				ft_send_int();
			else
				ft_send_char();
		}
		else if (signal == SIGUSR2)
		{
			if (get_data()->length_send == false)
			{
				get_data()->length_send = true;
				ft_send_char();
			}
			else
			{
				ft_putendl_fd("Message sended !", 1);
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction sig;

	if (argc == 3)
	{
		get_data()->bit_index = 0;
		get_data()->length_send = false;
		get_data()->server_pid = ft_atoi(argv[1]);
		get_data()->string = argv[2];
		get_data()->string_index = 0;
		get_data()->string_len = ft_strlen(argv[2]);
		sig.sa_sigaction = ft_receive_sort;
		sig.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		kill(get_data()->server_pid, SIGUSR1);
	}
	while (true)
		pause();
	return (0);
}