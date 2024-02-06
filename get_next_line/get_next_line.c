#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

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

void	*ft_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (n-- && (dst || src))
		dst[i - n] = src[i - n];
	return (dst);
}

char	*ft_strdup(char *str, size_t n)
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
	if (!*line)
		*line = ft_strdup("", 1);
	// ptr = ft_strchr(buf, '\n');
// 			if (ptr)
// 			{
// 				if (!line)
// 					line = ft_strdup(buf, BUFFER_SIZE);
// 				else
// 					line = str_join(line, ft_strdup(buf, ptr - buf));
// 				ft_memcpy(buf, ptr + 1, BUFFER_SIZE - (ptr - buf));
// 				break ;
// 			}
// 			else
// 				line = str_join(line, ft_strdup(buf, BUFFER_SIZE));
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
		printf("%s\n", ptr);
	}
	free(buf);
	// search_line(&ptr, &line);
	return (ptr );
}

// ptr = ft_strchr(buf, '\n');
// 			if (ptr)
// 			{
// 				if (!line)
// 					line = ft_strdup(buf, BUFFER_SIZE);
// 				else
// 					line = str_join(line, ft_strdup(buf, ptr - buf));
// 				ft_memcpy(buf, ptr + 1, BUFFER_SIZE - (ptr - buf));
// 				break ;
// 			}
// 			else
// 				line = str_join(line, ft_strdup(buf, BUFFER_SIZE));

int	main(void)
{
	char	*str2;
	int		fd;

	fd = open("file1", O_RDONLY, 0644);
	get_next_line(fd);
	while (1)
	{
		str2 = get_next_line(fd);
		printf("%s\n", str2);
		if (str2)
			free(str2);
		else
			break ;
	}
	close(fd);
	return (0);
}
