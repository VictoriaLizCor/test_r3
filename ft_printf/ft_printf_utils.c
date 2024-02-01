/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:01:55 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/15 15:23:48 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

int	ft_get_strsize(unsigned long num, int base)
{
	unsigned long	quotient;
	int				str_size;

	if (num == 0)
		return (1);
	str_size = 0;
	quotient = num;
	while (quotient > 0)
	{
		quotient = quotient / base;
		str_size++;
	}
	return (str_size);
}

void	ft_convert2base(char *str, int str_size, int base, unsigned long num)
{
	long long	remainder;

	while (str_size--)
	{
		remainder = num % base;
		if (remainder < 10)
			*(str + str_size) = '0' + remainder;
		else
			*(str + str_size) = 87 + remainder;
		num = num / base;
	}
}
