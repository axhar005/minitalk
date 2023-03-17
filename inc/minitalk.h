/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:55 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/16 16:43:16 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITAL_H

//includes
# include <unistd.h>

//structs

//prototypes
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif