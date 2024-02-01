/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:40:06 by lilizarr          #+#    #+#             */
/*   Updated: 2024/01/31 15:00:13 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.c"


int	main(void)
{
	char	*line;
	int		fd1;
	char	*str;
	int		i;

	i = 1;
	str = "ABCDEFGHIJ\nKLMN\nOPQRS\nTUVWXYZ\t\n1234567890\n";
	fd1 = open("file1", O_RDWR | O_CREAT, 0777);
	write(fd1, str, ft_strlen(str));
	close(fd1);
	str = NULL;
	sleep(1);
	fd1 = open("file1", O_RDONLY);;
	while (1)
	{
		line = get_next_line(fd1);
		printf("\nReturn: : ");
		if (line)
			printf("%s[%zu]\n", line, ft_strlen(line));
		else
		{
			printf("%s\n\n", (void *)0);
			break ;
		}
		free(line);
	}
	if (close(fd1) == -1)
	{
		printf("| %s |", str);
		return (1);
	}
	return (0);
}
