/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:39:09 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/15 15:11:49 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (n-- && (dest != NULL || src != NULL))
	{
		((char *)dest)[i - n] = (*(const char *)(src + (i - n)));
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;

	if (size == SIZE_MAX || count == SIZE_MAX)
		return (NULL);
	data = malloc(count * size);
	if (data)
		ft_memset(data, 0, count * size);
	else
		return (NULL);
	return (data);
}

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

char	*ft_strdup_len(char *s1, size_t n)
{
	char	*aux;

	aux = (char *)malloc(n + 1);
	if (aux == NULL)
		return (NULL);
	aux = ft_memcpy(aux, s1, n);
	aux[n] = '\0';
	return (aux);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, int free_str)
{
	char	*sj;

	if (s1 && s2)
	{
		sj = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (sj)
		{
			ft_memcpy(sj, s1, ft_strlen(s1));
			ft_memcpy(sj + ft_strlen(s1), s2, ft_strlen(s2) + 1);
			if (free_str == 1)
				free((void *)s1);
			else if (free_str == 2)
				free((void *)s2);
			else
			{
				free((void *)s1);
				free((void *)s2);
			}
			return ((char *)sj);
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(*s) && !c)
		return ((char *)s);
	return (NULL);
}

static int	power_10(int power)
{
	int	result;
	int	i;

	i = 0;
	result = 1;
	while (i++ <= power)
		result *= 10;
	return (result);
}

static char	*create_string(int n_cpy, int s_size, int sign_char, int sign_num)
{
	char	*s;
	int		cnt;
	int		res;

	cnt = 0;
	s = ft_calloc((s_size + sign_char + 1), sizeof(char));
	if (!s)
		return (NULL);
	if (sign_char == 2 && s)
	{
		s[cnt] = '-';
		cnt++;
		sign_num = -1;
	}
	while (--s_size >= 0)
	{
		res = (n_cpy / power_10(s_size)) * sign_num;
		n_cpy = n_cpy % (power_10(s_size));
		s[cnt] = res + '0';
		cnt++;
	}
	s[cnt] = (sign_num * n_cpy) + '0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		s_size;
	int		n_cpy;
	int		sign_char;
	int		sign_num;

	s_size = 0;
	sign_char = 1;
	n_cpy = n;
	sign_num = -1;
	if (n < 0)
	{
		sign_num = 1;
		sign_char++;
	}
	while ((sign_num * n_cpy) <= -10)
	{
		n_cpy = n_cpy / 10;
		s_size++;
	}
	n_cpy = n * sign_num;
	return (create_string(n_cpy, s_size, sign_char, sign_num));
}
