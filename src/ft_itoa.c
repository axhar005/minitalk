/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:44:27 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/16 15:21:07 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_num(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*check(char *new, int i, int sign, long int num)
{
	while (i >= 0)
	{
		if (i == 0 && sign == 1)
		{
			new[i] = '-';
			break ;
		}
		new[i] = (num % 10) + 48;
		num /= 10;
		i--;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			i;
	int			num_len;
	int			sign;
	char		*new;

	sign = 0;
	num = n;
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	num_len = check_num(num);
	if (sign == 0)
		i = num_len - 1;
	else
		i = num_len;
	new = ft_calloc(num_len + 1 + sign, sizeof(char));
	if (!new)
		return (NULL);
	return (check(new, i, sign, num));
}
