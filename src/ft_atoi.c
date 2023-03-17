/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:35:05 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/16 16:41:07 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int	check(char *str, int i)
{
	int	res;

	res = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}
	return (check((char *)str, i) * sign);
}
