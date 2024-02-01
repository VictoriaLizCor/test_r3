/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/15 15:15:07 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/* struct t_printf
**	f_width	->	field width		%5f 
**	presc 	->	precision 		%5.2f
**	prd		->	period
**	zero	->	zero padding	# printf("%07d", 012);
**	dash	-> -
**	sign	->	pos or neg number
**	n_zero	->	is number 	zero
**	perc	->	%
**	c_spc	-> character specifier
**	c_space	->	space flag ' ' 
**	c_hash	->	# flag
*/
/* cspdiuxX%
** %[flags][width][.precision][length]specifier
** struct content, specifier, len
** ft_strchr(" +-\t\n\r\v\f", *(sp + 1))
** 55 + remainder for uppercase
*/
typedef struct s_printf
{
	va_list		args;
	char		c_spc;
	const void	*ptr;
}	t_printf;

void	ft_putstr(char *s);
void	ft_putchar(char c);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_toupper(int c);
char	*ft_itoa(int n);
char	*ft_strdup_len(char *s1, size_t n);
char	*ft_strjoin_gnl(char const *s1, char const *s2, int free_str);
int		ft_printf(const char *format, ...);
void	ft_printf_str(t_printf **content, int *ret);
void	ft_printf_int(t_printf **content, int *ret);
void	ft_printf_char(t_printf **content, int *ret);
void	ft_printf_upx(t_printf **content, int *ret, int base);
int		ft_get_strsize(unsigned long num, int base);
void	ft_convert2base(char *str, int str_size, int base, unsigned long num);
int		ft_printf(const char *format, ...);
#endif