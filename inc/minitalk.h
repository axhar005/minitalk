/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:55 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/31 17:38:11 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define CHAR_SIZE 8
# define INT_SIZE 32

//includes
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//structs
typedef struct s_sdata
{
	unsigned char	*string;
	char			c;
	int				bit_index;
	int				index;
	int				length;
	pid_t			server_pid;
	pid_t			client_pid;
}					t_sdata;

typedef struct s_cdata
{
    pid_t server_pid;
	int length;
	int index;
	char *string;
}					t_cdata;

//prototypes
char				*ft_itoa(int n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(char *str);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_putchar_fd(char c, int fd);
void				*ft_sfree(void *str);
int					ft_putustr_fd(unsigned char *s, int fd);

#endif