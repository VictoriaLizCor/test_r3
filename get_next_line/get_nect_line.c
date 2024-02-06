#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	ft_strlen(const char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

char	*ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (!c)
		return (str);
	return (NULL);
}

void	*ft_memcpy(char *dst, char *src, int n)
{
	size_t	i;

	i = n - 1;
	while (n-- && (dst || src))
		dst[i - n] = src[i - n];
	return (dst);
}

char	*ft_strdup(char *str, int n)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return ((void *)0);
	new_str = ft_memcpy(new_str, str, n);
	new_str[n] = '\0';
	return (new_str);
}

char	*str_join(char *s1, char *s2)
{
	char	*str_join;

	if (!s1 || !s2)
		return ((void *)0);
	str_join = ft_strdup("", ft_strlen(s1) + ft_strlen(s2));
	ft_memcpy(str_join, s1, ft_strlen(s1));
	ft_memcpy(str_join + ft_strlen(s1), s2, ft_strlen(s2));
	if (s1)
		free(s1);
	return (str_join);
}

void	search_line(char **ptr, char **line)
{
	char *tmp;
	int dif;

	dif = 0;
	printf("\n-----PTR-------\n");
	printf("%s", *ptr);
	printf("\n---------\n");
	if (!*ptr)
		return ;
	tmp = ft_strchr(*ptr, '\n');
	if (tmp)
	{
		dif = tmp - (*ptr);
		*line = ft_strdup(*ptr, dif);
		if (tmp + 1)
			tmp = ft_strdup(tmp + 1, ft_strlen(tmp + 1));
		else
			tmp = ft_strdup(tmp, ft_strlen(tmp));
		if (*ptr)
			free(*ptr);
		*ptr = tmp;
	}
	else
	{
		*line = ft_strdup(*ptr, ft_strlen(*ptr));
		if (*ptr)
			free(*ptr);
		*ptr = NULL;
	}
	printf("diff [%d] \n", dif);
	if (*line)
		printf("[%d]", ft_strlen(*line));
	printf("LINE-> %s", *line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*ptr;
	int			ret;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return ((void *)0);
	line = (void *)0;
	buf = ft_strdup("", BUFFER_SIZE - 1);
	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret)
			printf("%d --------- %s\n", ret, buf);
		if (ret <= 0)
			break ;
		if (!ptr)
			ptr = ft_strdup(buf, BUFFER_SIZE);
		else
			ptr = str_join(ptr, buf);
	}
	if (buf)
		free(buf);
	search_line(&ptr, &line);
	return (line);
}

int	main(void)
{
	char	*str2;
	int		fd;
	int 	i;

	i = 1;
	fd = open("file1", O_RDONLY, 0644);
	while (1 && i < 10)
	{
		str2 = get_next_line(fd);
		printf("\n[%d]RETURN->", i++);
		if(str2)
		{
			printf("[%d] ", ft_strlen(str2));
			printf("| %d : ", str2[ft_strlen(str2) - 1]);
		}
		printf("%s", str2);
		if (str2)
			free(str2);
		else
			break ;
	}
	printf("\n[%d]ft_len-> %s", ft_strlen("abcdf\n"), "abcdf\n");
	printf("\\n = [%d]\n", '\n');
	close(fd);
	return (0);
}