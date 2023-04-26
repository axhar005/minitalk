/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:35:42 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/25 23:43:44 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//server
//This function draw server info
void	draw_server_info(t_sdata *data)
{
	ft_putendl_fd("\033[34;1m----------------------------------------", 1);
	ft_putstr_fd("|             ", 1);
	ft_putendl_fd("\033[33;1mServer Info\033[34;1m              |", 1);
	ft_putendl_fd("----------------------------------------", 1);
	ft_putstr_fd("\033[33;1m~ PID :\033[36;1m ", 1);
	ft_putnbr_fd(data->server_pid, 1);
	ft_putstr_fd("\033[0m\n", 1);
}

//This function initializes t_sdata struct
void	init_server_struct(t_sdata *data)
{
	data->string = ft_sfree(data->string);
	data->bit_index = 0;
	data->c = 0;
	data->server_pid = getpid();
	data->client_pid = 0;
	data->string_index = 0;
	data->string_len = 0;
	data->start_recieve = false;
}

//This function add c char to the string
void	add_char(t_sdata *data)
{
	if (!data->string)
		data->string = ft_calloc(data->string_len + 1, sizeof(char));
		data->string[data->string_index] = data->c;
	if (data->string_index == (data->string_len - 1))
	{
		kill(data->client_pid, SIGUSR2);
		ft_putendl_fd("\033[37;1m", 1);
		ft_putendl_fd(data->string, 1);
		ft_putstr_fd("\033[0m\n", 1);
		init_server_struct(data);
		return ;
	}
	data->string_index++;
}

//client
//This function initializes t_cdata struct
void	ft_initialize_cstruct(t_cdata *data, char **argv)
{
	data->bit_index = 0;
	data->length_send = false;
	data->server_pid = ft_atoi(argv[1]);
	data->string = argv[2];
	data->string_index = 0;
	data->string_len = ft_strlen(argv[2]);
}
