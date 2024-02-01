#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

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

void	print_list(t_list **list)
{
	t_list	*print;
	int		i;

	i = 0;
	print = *list;
	while (print)
	{
		print = print->next;
		i++;
	}
	print = *list;
	printf("\n------------- List HEAD Address : %p\t NODES: %d\n", *list, i);
	while (print)
	{
		printf("%s", print->str);
		print = print->next;
		i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (n-- && (dest != NULL || src != NULL))
		((char *)dest)[i - n] = (*(const char *)(src + (i - n)));
	return (dest);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;

	if (s1 && s2)
	{
		str_join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!str_join)
			return (NULL);
		ft_memcpy(str_join, s1, ft_strlen(s1));
		ft_memcpy(str_join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
		free((void *)s1);
		return ((char *)str_join);
	}
	else
		return (NULL);
}

void	add_node_to_list(t_list **list, char *read_buffer, int ret)
{
	t_list	*new_node;
	t_list	*last;

	new_node = (t_list *)malloc (sizeof(t_list));
	if (!new_node)
		*list = NULL;
	new_node->str = ft_strdup_len(read_buffer, ret);
	new_node->next = NULL;
	if (!(*list))
		*list = new_node;
	else
	{
		last = *list;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		while (last->next != NULL)
			last = last->next;
	}
	print_list(list);
}

void	free_node_list(void **list)
{
	t_list	*tmp;
	t_list	*to_erase;
	int		i;

	i = 0;
	to_erase = *list;
	tmp = to_erase->next;
	free(to_erase->str);
	free(to_erase);
	*list = tmp;
}

void	search_line_ext(t_list **list, char **line, char *ptr)
{
	int		diff_nl;
	char	*tmp;

	diff_nl = ptr - ((*list)->str);
	if (!(*line))
		*line = ft_strdup_len((*list)->str, diff_nl + 1);
	else
	{
		tmp = ft_strdup_len((*list)->str, diff_nl + 1);
		*line = ft_strjoin(*line, tmp);
		free(tmp);
	}
	if ((ft_strlen(ptr + 1)))
	{
		tmp = ft_strdup_len(ptr + 1, ft_strlen(ptr + 1));
		free((*list)->str);
		(*list)->str = tmp;
	}
	else
		free_node_list((void *)(*&list));
}

void	search_line(t_list **list, char **line)
{
	char	*ptr;

	while ((*list))
	{
		ptr = ft_strchr((*list)->str, '\n');
		if (ptr)
		{
			search_line_ext((&*list), (&*line), ptr);
			return ;
		}
		else
		{
			if (!(*line))
				*line = ft_strdup_len((*list)->str, ft_strlen((*list)->str));
			else
				*line = ft_strjoin(*line, (*list)->str);
			free_node_list((void *)(*&list));
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list		*list;
	int					ret;
	char				*line;
	char				*read_buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_buffer = (char *)malloc(BUFFER_SIZE);
	if (!read_buffer)
		return (NULL);
	read_buffer[BUFFER_SIZE] = 0;
	while (1)
	{
		ret = read(fd, read_buffer, BUFFER_SIZE);
		if (!ret || ret < 0)
			break ;
		else
			add_node_to_list(&list, read_buffer, ret);
	}
	free(read_buffer);
	print_list(&list);
	search_line(&list, &line);
	return (&*line);
}
