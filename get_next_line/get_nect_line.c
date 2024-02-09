#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char *str)
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
	if (!c && !*str)
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

void	check_after_string_data(char *str, int extra, char *id)
{
	int		i;
	char	*buf;

	if (str)
	{
		i = 0;
		buf = str;
		printf("\n%s->", id);
		while (i <= ft_strlen(str) + extra)
		{
			if (!ft_strchr("\t\n\r\v\f", buf[i]))
				printf("[ %c ]", *(buf + i));
			else
				printf("[ '\\%d' ]", *(buf + i));
			i++;
		}
		printf("\n---------\n");
	}
	else
		printf("\n%s->%s", id, (void *)0);
}

void	search_line(char **ptr, char **line)
{
	char	*tmp;
	int		dif;

	dif = 0;
	printf("ptr->%s| %d\n", *ptr, ft_strlen(*ptr));
	tmp = ft_strchr(*ptr, '\n');
	if (tmp)
	{
		dif = tmp - (*ptr);
		*line = ft_strdup(*ptr, dif + 1);
		if (tmp + 1)
			tmp = ft_strdup(tmp + 1, ft_strlen(tmp + 1));
		else
			tmp = ft_strdup(tmp, ft_strlen(tmp));
	}
	else if (**ptr)
		*line = ft_strdup(*ptr, ft_strlen(*ptr));
	if (*ptr)
		free(*ptr);
	*ptr = tmp;
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*ptr;
	int			ret;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return ((void *)0);
	line = (void *)0;
	buf = ft_strdup("", BUFFER_SIZE);
	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		printf(" ------------- RET = %d -------------\n", ret);
		if (ret <= 0)
			break ;
		if (!ptr)
			ptr = ft_strdup(buf, ret);
		else
			ptr = str_join(ptr, buf);
	}
	if (buf)
		free(buf);
	check_after_string_data(ptr, 2, "ptr");
	if (ptr)
		search_line(&ptr, &line);
	check_after_string_data(line, 2, "line");
	if (line)
		printf("line->%s| %d\n", line, ft_strlen(line));
	else
		printf("\n%s", line);
	return (line);
}

int	main(void)
{
	char	*str2;
	int		fd;
	int		i;

	i = 1;
	fd = open("./files/file1", O_RDONLY, 0644);
	// fd = open("../../success/Rank03/get_next_line/files/41_with_nl", O_RDONLY, 0644);
	// fd = open("../../success/Rank03/get_next_line/files/file1", O_RDONLY, 0644);
	while (1 && i++ < 10)
	{
		str2 = get_next_line(fd);
		// printf("[%d]RETURN->", i++);
		// if (str2)
		// {
		// 	printf("[%d] ", ft_strlen(str2));
		// 	printf("| %d : ", str2[ft_strlen(str2) - 1]);
		// }
		// printf("%s", str2);
		if (str2)
			free(str2);
		else
			break ;
	}
	printf("\n----\n");
	close(fd);
	// fd = open("../../success/Rank03/get_next_line/files/nl", O_RDONLY, 0644);
	// while (1)
	// {
	// 	str2 = get_next_line(fd);
	// 	printf("[%d]RETURN->", i++);
	// 	check_after_string_data(str2, 2);
	// 	if (str2)
	// 		free(str2);
	// 	else
	// 		break ;
	// }
	// close(fd);
	// printf("\n----\n");
	return (0);
}
