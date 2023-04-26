/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:55 by oboucher          #+#    #+#             */
/*   Updated: 2023/04/26 14:59:58 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define CHAR_SIZE 8
# define INT_SIZE 32

//includes
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

//structs
typedef struct s_sdata
{
	pid_t	server_pid;
	pid_t	client_pid;
	bool	start_recieve;
	int		string_len;
	int		string_index;
	int		bit_index;
	char	c;
	int		tick;
	char	*string;
}			t_sdata;

typedef struct s_cdata
{
	pid_t	server_pid;
	bool	length_send;
	int		string_len;
	int		string_index;
	int		bit_index;
	int		tick;
	char	*string;
}			t_cdata;

//prototypes
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_putchar_fd(char c, int fd);
void		*ft_sfree(void *str);
void		init_server_struct(t_sdata *data);
void		draw_server_info(t_sdata *data);
void		ft_initialize_cstruct(t_cdata *data, char **argv);
void		add_char(t_sdata *data);

#endif